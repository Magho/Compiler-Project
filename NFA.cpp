#include <iostream>
#include "NFA.h"

NFA::NFA(vector<Node *> graph, vector<Node *> startNodes, vector<Node *> finalNodes) {
    this->graph = std::move(graph);
    this->startNodes = std::move(startNodes);
    this->finalNodes = std::move(finalNodes);
}

int NFA::getVertexCount() {
    return static_cast<int>(this->graph.size());
}

vector<Node*> NFA::getStartNodes() {
    return this->startNodes;
}

vector<Node*> NFA::getFinalNodes() {
    return this->finalNodes;
}

vector<Node *> NFA::getGraphNodes() {
    return this->graph;
}

vector<Node*> NFA::epsilonClosure(vector<Node*> nodes) {
    vector<Node*> result; // result here is a vector
    for (auto &node : nodes) {
        vector<Transition*> trans = node->getPossibleTransitions();
        for (auto &tran : trans) {
            if (tran->transitionSymbol == '~'){
                result.push_back(tran->toNode);
                epsilonClosureRecursive(tran->toNode, &result);
            }
        }
    }
    return result;
}

void NFA::epsilonClosureRecursive(Node *node, vector<Node*>* result) {
    // result here is pointer to the vector in epsilonClosure function
    if (node->getPossibleTransitions().empty()){
        return;
    } else {
        vector<Transition*> trans = node->getPossibleTransitions();
        for (auto &tran : trans) {
            if (tran->transitionSymbol == '~'){
                result->push_back(tran->toNode);
                epsilonClosureRecursive(tran->toNode, result);
            }
        }
    }
}

void NFA::printNFA() {
    for (int i = 0; i < this->startNodes.size(); ++i) {
        printRecursive(startNodes[i]);
    }
}

void NFA::printRecursive(Node* node) {
    if (node->getPossibleTransitions().empty()){
        cout << node->getNodeNumber() << "#" << endl;
        return;
    }
    cout << node->getNodeNumber() << "--> ";
    vector<Transition*> trans = node->getPossibleTransitions();
    for (auto &tran : trans) {
        printRecursive(tran->toNode);
    }
}
