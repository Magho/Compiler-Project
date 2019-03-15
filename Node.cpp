#include "Node.h"

Node::Node(int Number, bool start, bool final, string tokenName) {
    this->Number     =   Number    ;
    this->start      =   start     ;
    this->final      =   final     ;
    this->tokenName  =   tokenName ;
}

void Node::addTransition(Node node_to, char transitionSymbol) {

}

vector<Transition> Node::getPossibleTransitions() {

}

Node Node::getNextNode(char transitionSymbol) {

}
