#ifndef Transition_H
#define Transition_H
#include<vector>
#include<string>

using namespace std;


class Node;

class Transition {
public :

    Node* toNode; // pointer to the node -- we don't want a copy we need the node itself
    char transitionSymbol;

    Transition(Node* node, char symbol ) {
        this->toNode = node;
        this->transitionSymbol = symbol;
    };
};
#endif
