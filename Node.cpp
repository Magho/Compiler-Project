#include <utility>
#include <utility>
#include "Node.h"
#define EPSILON 163

Node::Node(int Number, bool start, bool final,int priority, string tokenName) {
    this->nodeNumber     =   Number    ;
    this->start      =   start     ;
    this->final      =   final     ;
    this->priority   =   priority  ;
    this->tokenName  = std::move(tokenName);
}

void Node::addTransition(Node* node_to, char transitionSymbol) {
    if (transitionSymbol != char(EPSILON)) {
        node_to->lexeme = this->lexeme + transitionSymbol;
    }
    // used dynamic allocation to avoid deleting this trans when going out of scope
    Transition *trans  = new Transition (node_to, transitionSymbol);
    this->transitions.push_back(trans);
}

vector<Transition*> Node::getPossibleTransitions() {
    return this->transitions;
}

vector<Node*> Node::getNextNode(char transSymbol) {
    vector<Node*> nextNodes;
    for (auto &transition : this->transitions) {
        if (transition->transitionSymbol == transSymbol) {
            // toNode is a pointer so used * to access its value
            nextNodes.push_back(transition->toNode);
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

void Node::setStart() {
    this->start = true;
}

void Node::setFinal() {
    this->final = true;
}

void Node::removeStart() {
    this->start = false;
}

void Node::removeFinal() {
    this->final = false;
}

string Node::getLexeme() {
    // if no token name return empty string
    return this->lexeme;
}

int Node::getNodeNumber() {
    return this->nodeNumber;
}

void Node::setNodeNumber(int nodenumber) {
    this->nodeNumber = nodenumber;
}

int Node::getPriority() {
    return this->priority;
}

string Node::getTokenName() {
    return this->tokenName;
}