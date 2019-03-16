#include <utility>
#include "Node.h"

Node::Node(int Number, bool start, bool final, string tokenName) {
    this->Number     =   Number    ;
    this->start      =   start     ;
    this->final      =   final     ;
    this->tokenName  = std::move(tokenName);
}

void Node::addTransition(Node* node_to, char transitionSymbol) {
    // used dynamic allocation to avoid deleting this trans when going out of scope
    Transition *trans  = new Transition (node_to, transitionSymbol);
    this->transitions.push_back(trans);
}

vector<Transition*> Node::getPossibleTransitions() {
    return this->transitions;
}

vector<Node> Node::getNextNode(char transSymbol) {
    vector<Node> nextNodes;
    for (auto &transition : this->transitions) {
        if (transition->transitionSymbol == transSymbol) {
            // toNode is a pointer so used * to access its value
            nextNodes.push_back(*transition->toNode);
        }
    }
    return nextNodes;
}

bool Node::isStart() {
    return this->start;
}

bool Node::isFinal() {
    return this->final;
}

string Node::getTokenName() {
    // if no token name return empty string
    return this->tokenName;
}

int Node::getNodeNumber() {
    return this->Number;
}