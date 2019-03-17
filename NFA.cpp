#include <utility>
#include <iostream>
#include "NFA.h"
#define EPSILON 163

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

NFA* NFA::kleneeClosure(int priority, int* nodeNumber, string tokenName) {

    // used dynamic allocation to avoid deleting this Node when going out of scope
    Node* start = new Node (++*nodeNumber, true, false, priority, tokenName);
    Node* final = new Node (++*nodeNumber, true, false, priority, tokenName);

    vector<Node*> nfaStartNodes = this->getStartNodes();
    vector<Node*> nfaFinalNodes = this->getFinalNodes();
    vector<Node*> nfaGraph;
    for (auto &graphNode : this->getGraphNodes()){
        nfaGraph.push_back(graphNode);
    }
    nfaGraph.push_back(start);
    nfaGraph.push_back(final);

    for (auto &nfaStartNode : nfaStartNodes) {
        start->addTransition(nfaStartNode, char(EPSILON));
    }
    for (auto &nfaFinalNode : nfaFinalNodes) {
        nfaFinalNode->addTransition(final, char(EPSILON));
    }
    for (auto &nfaFinalNode : nfaFinalNodes) {
        for (auto &nfaStartNode : nfaStartNodes) {
            nfaFinalNode->addTransition(nfaStartNode,char(EPSILON));
            nfaStartNode->removeStart();
        }
        nfaFinalNode->removeFinal();
    }

    start->addTransition(final,char(EPSILON));

    vector<Node*> ResultStartNodes;
    ResultStartNodes.push_back(start);
    vector<Node*> ResultFinalNodes;
    ResultFinalNodes.push_back(final);

    NFA* result = new NFA (nfaGraph, ResultStartNodes, ResultFinalNodes, this->getTokenName());

    return result;
}

NFA* NFA::positiveClosure(int* nodeNumber) {

    vector<Node*> nfaStartNodes = this->getStartNodes();
    vector<Node*> nfaFinalNodes = this->getFinalNodes();
    vector<Node*> nfa1Graph = this->getGraphNodes();
    int priority = nfa1Graph.back()->getPriority();

    NFA* result = new NFA (nfa1Graph, nfaStartNodes, nfaFinalNodes, this->getTokenName());
    NFA* originalCopy = new NFA (nfa1Graph, nfaStartNodes, nfaFinalNodes, this->getTokenName());
    result = result->kleneeClosure(priority, nodeNumber ,this->getTokenName());
    RenameNodes(nodeNumber, originalCopy);
    return originalCopy->concatenate(*result,priority, nodeNumber , this->getTokenName());
}

void NFA::RenameNodes(int *nodeNumber, NFA* nfa) {
    vector<Node*> nfaGraph = nfa->getGraphNodes();
    for (auto &i : nfaGraph) {
        i->setNodeNumber(++*nodeNumber);
    }
}

NFA* NFA::concatenate(NFA nfa, int priority, int* nodeNumber, string tokenName) {

    vector<Node*> nfa1StartNodes = this->getStartNodes();
    vector<Node*> nfa1FinalNodes = this->getFinalNodes();
    vector<Node*> nfa2FinalNodes = nfa.getFinalNodes();
    vector<Node*> nfa2StartNodes = nfa.getStartNodes();
    vector<Node*> nfa1Graph = this->getGraphNodes();
    vector<Node*> nfa2Graph = nfa.getGraphNodes();

    // used dynamic allocation to avoid deleting this Node when going out of scope
    Node* start = new Node (++*nodeNumber, true, false, priority, tokenName);
    Node* final = new Node (++*nodeNumber, true, false, priority, tokenName);

    for (auto &nfa1StartNode : nfa1StartNodes) {
        start->addTransition(nfa1StartNode, char(EPSILON));
        nfa1StartNode->removeStart();
    }
    for (auto &nfa2FinalNode : nfa2FinalNodes) {
        nfa2FinalNode->addTransition(final, char(EPSILON));
        nfa2FinalNode->removeFinal();
    }
    for (auto &nfa1FinalNode : nfa1FinalNodes) {
        for (auto &nfa2StartNode : nfa2StartNodes) {
            nfa1FinalNode->addTransition(nfa2StartNode,char(EPSILON));
            nfa2StartNode->removeStart();
        }
        nfa1FinalNode->removeFinal();
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

    NFA* result = new NFA (ResultGraph, ResultStartNodes, ResultFinalNodes, this->getTokenName());

    return result;
}

NFA* NFA::orOperator(NFA nfa, int priority, int* nodeNumber, string tokenName) {

    vector<Node*> nfa1StartNodes = this->getStartNodes();
    vector<Node*> nfa1FinalNodes = this->getFinalNodes();
    vector<Node*> nfa2StartNodes = nfa.getStartNodes();
    vector<Node*> nfa2FinalNodes = nfa.getFinalNodes();
    vector<Node*> nfa1Graph = this->getGraphNodes();
    vector<Node*> nfa2Graph = nfa.getGraphNodes();

    // used dynamic allocation to avoid deleting this Node when going out of scope
    Node* start = new Node (++*nodeNumber, true, false, priority, tokenName);
    Node* final = new Node (++*nodeNumber, true, false, priority, tokenName);

    for (auto &nfa1StartNode : nfa1StartNodes) {
        start->addTransition(nfa1StartNode, char(EPSILON));
        nfa1StartNode->removeStart();
    }
    for (auto &nfa2StartNode : nfa2StartNodes) {
        start->addTransition(nfa2StartNode, char(EPSILON));
        nfa2StartNode->removeStart();
    }
    for (auto &nfa1FinalNode : nfa1FinalNodes) {
        nfa1FinalNode->addTransition(final, char(EPSILON));
        nfa1FinalNode->removeFinal();
    }
    for (auto &nfa2FinalNode : nfa2FinalNodes) {
        nfa2FinalNode->addTransition(final, char(EPSILON));
        nfa2FinalNode->removeFinal();
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

    NFA* result = new NFA (ResultGraph, ResultStartNodes, ResultFinalNodes, this->getTokenName());

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
        printRecursive(startNodes[i], 0);
    }
}

void NFA::printRecursive(Node* node, int depth) {
    if (node->getPossibleTransitions().empty()){
        cout << node->getNodeNumber() << "#" << endl;
        return;
    }
    cout << node->getNodeNumber() << "--> ";
    vector<Transition*> trans = node->getPossibleTransitions();
    int i = 0;
    for (auto &tran : trans) {
        if (i != 0){
            for (int j = 0; j < depth; j++) {
                cout << "     ";
            }
            cout << "|" << "--> ";
        }
        printRecursive(tran->toNode, depth+1);
        i++;
    }
}
