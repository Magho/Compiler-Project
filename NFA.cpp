#include <utility>

#include <iostream>
#include "NFA.h"

NFA::NFA(vector<Node*> graph, vector<Node*> startNodes, vector<Node*> finalNodes, string tokenName) {
    this->graph = std::move(graph);
    this->startNodes = std::move(startNodes);
    this->finalNodes = std::move(finalNodes);
    this->tokenName = std::move(tokenName);
}


vector<Node*> NFA::getStartNodes() {
    return this->startNodes;
}

vector<Node*> NFA::getFinalNodes() {
    return this->finalNodes;
}

vector<Node*> NFA::getGraphNodes() {
    return this->graph;
}

vector<Node*> NFA::epsilonClosure(vector<Node*> nodes) {
    vector<Node*> result; // result here is a vector
    for (auto &node : nodes) {
        result.push_back(node);
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

NFA NFA::klenee() {

    // used dynamic allocation to avoid deleting this Node when going out of scope
    Node* start = new Node (0, true, false);
    Node* final = new Node (1, true, false);

    vector<Node*> nfaStartNodes = this->getStartNodes();
    vector<Node*> nfaFinalNodes = this->getFinalNodes();
    vector<Node*> nfaGraph;
    for (auto &graphNode : this->getGraphNodes()){
        nfaGraph.push_back(graphNode);
    }
    nfaGraph.push_back(start);
    nfaGraph.push_back(final);

    for (auto &nfaStartNode : nfaStartNodes) {
        start->addTransition(nfaStartNode, '~');
    }
    for (auto &nfaFinalNode : nfaFinalNodes) {
        nfaFinalNode->addTransition(final, '~');
    }
    for (auto &nfaFinalNode : nfaFinalNodes) {
        for (auto &nfaStartNode : nfaStartNodes) {
            nfaFinalNode->addTransition(nfaStartNode,'~');
        }
    }

    start->addTransition(final,'~');

    vector<Node*> ResultStartNodes;
    ResultStartNodes.push_back(start);
    vector<Node*> ResultFinalNodes;
    ResultFinalNodes.push_back(final);

    NFA result (nfaGraph, ResultStartNodes, ResultFinalNodes, this->getTokenName());

    return result;
}

NFA NFA::concatenate(NFA nfa) {

    vector<Node*> nfaStartNodes = this->getStartNodes();
    vector<Node*> nfaFinalNodes = nfa.getFinalNodes();
    vector<Node*> nfa1Graph = this->getGraphNodes();
    vector<Node*> nfa2Graph = nfa.getGraphNodes();

    // used dynamic allocation to avoid deleting this Node when going out of scope
    Node* start = new Node (0, true, false);
    Node* final = new Node (1, true, false);

    for (auto &nfaStartNode : nfaStartNodes) {
        start->addTransition(nfaStartNode, '~');
    }
    for (auto &nfaFinalNode : nfaFinalNodes) {
        nfaFinalNode->addTransition(final, '~');
    }
    for (auto &nfaStartNode : nfaStartNodes) {
        for (auto &nfaFinalNode : nfaFinalNodes) {
            nfaStartNode->addTransition(nfaFinalNode,'~');
        }
    }

    vector<Node*> ResultStartNodes;
    ResultStartNodes.push_back(start);
    vector<Node*> ResultFinalNodes;
    ResultFinalNodes.push_back(final);
    vector<Node*> ResultGraph;

    for (auto i : nfa1Graph) {
        ResultGraph.push_back(i);
    }
    for (auto i : nfa2Graph) {
        ResultGraph.push_back(i);
    }

    ResultGraph.push_back(start);
    ResultGraph.push_back(final);

    NFA result(ResultGraph, ResultStartNodes, ResultFinalNodes, this->getTokenName());

    return result;
}

NFA NFA::orOperator(NFA nfa) {

    vector<Node*> nfaStartNodes = this->getStartNodes();
    vector<Node*> nfaFinalNodes = nfa.getFinalNodes();
    vector<Node*> nfa1Graph = this->getGraphNodes();
    vector<Node*> nfa2Graph = nfa.getGraphNodes();

    // used dynamic allocation to avoid deleting this Node when going out of scope
    Node* start = new Node (0, true, false);
    Node* final = new Node (1, true, false);

    for (auto &nfaStartNode : nfaStartNodes) {
        start->addTransition(nfaStartNode, '~');
    }
    for (auto &nfaFinalNode : nfaFinalNodes) {
        nfaFinalNode->addTransition(final, '~');
    }

    vector<Node*> ResultStartNodes;
    ResultStartNodes.push_back(start);
    vector<Node*> ResultFinalNodes;
    ResultFinalNodes.push_back(final);
    vector<Node*> ResultGraph;

    for (auto i : nfa1Graph) {
        ResultGraph.push_back(i);
    }
    for (auto i : nfa2Graph) {
        ResultGraph.push_back(i);
    }

    ResultGraph.push_back(start);
    ResultGraph.push_back(final);

    NFA result(ResultGraph, ResultStartNodes, ResultFinalNodes, this->getTokenName());

    return result;
}

int NFA::getVertexCount() {
    return static_cast<int>(this->graph.size());
}

string NFA::getTokenName() {
    return this->tokenName;
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
