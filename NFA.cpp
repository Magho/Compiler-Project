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
    Node* final = new Node (++*nodeNumber, false, true, priority, tokenName);

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
    vector<Node*> nfaGraph = this->getGraphNodes();
    int priority = nfaGraph.back()->getPriority();
    string tokenName =  this->getTokenName();

    NFA* result = new NFA (nfaGraph, nfaStartNodes, nfaFinalNodes, tokenName);
    NFA* originalCopy = this->CreateCopyOfNFA(nodeNumber);
    vector<Node*> nfa1Graph = originalCopy->getGraphNodes();
    // 0             , 1             , ...
    // 0+graph.size(), 1+graph.size(), ...
    int counter = 0;
    int size = nfaGraph.size();
    for (auto &i : nfaGraph) {
        vector<Transition*> trans = i->getPossibleTransitions();
        for (auto &tran : trans) {
            for (int j = 0; j < nfa1Graph.size(); ++j) {
                if(nfa1Graph[j]->getNodeNumber() == tran->toNode->getNodeNumber()+ size){
                    nfa1Graph[counter]->addTransition(nfa1Graph[j], tran->transitionSymbol);
                }
            }
        }
        counter++;
    }

    result = result->kleneeClosure(priority, nodeNumber ,tokenName);
    originalCopy = originalCopy->concatenate(*result,priority, nodeNumber , tokenName);
    return originalCopy;
}

NFA* NFA::CreateCopyOfNFA(int *nodeNumber) {

    vector<Node*>* nfa1StartNodes = new vector<Node*>;
    vector<Node*>* nfa1FinalNodes = new vector<Node*>;
    vector<Node*>* nfa1Graph = new vector<Node*>;
    vector<Node*> nfaGraph = this->getGraphNodes();

    for (auto &i : nfaGraph) {
        Node* node = new Node (++*nodeNumber, i->isStart(), i->isFinal(), i->getPriority(), i->getTokenName());
        nfa1Graph->push_back(node);
        if(i->isStart()){
            nfa1StartNodes->push_back(node);
        } else if (i->isFinal()){
            nfa1FinalNodes->push_back(node);
        }
    }
    NFA* result = new NFA (*nfa1Graph, *nfa1StartNodes, *nfa1FinalNodes, this->getTokenName());
    return result;
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
    Node* final = new Node (++*nodeNumber, false, true, priority, tokenName);

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
    Node* final = new Node (++*nodeNumber, false, true, priority, tokenName);

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
    map<int, bool> map1;
    for (int j = 0; j < this->graph.size(); ++j) {
        map1.insert(pair<int, bool>(graph[j]->getNodeNumber(), false));
    }
    for (int i = 0; i < this->startNodes.size(); ++i) {
        printRecursive(startNodes[i], 0, &map1);
    }
}

void NFA::printRecursive(Node* node, int depth, map<int, bool>* map1) {
    bool checkedBefore = false;
    map<int, bool>::iterator itr;
    for (itr = map1->begin(); itr != map1->end(); ++itr) {
        if (node->getNodeNumber() == itr->first) {
            if(itr->second) {
                checkedBefore = true;
            } else{
                itr->second = true;
            }
        }
    }
    if (checkedBefore){
        if (node->getNodeNumber() < 10){
            cout << node->getNodeNumber()  << " " << endl;
        } else {
            cout << node->getNodeNumber() << endl;
        }
        return;
    }
    else if (node->getPossibleTransitions().empty()){
        cout << node->getNodeNumber() << "#" << endl;
        return;
    }

    vector<Transition*> trans = node->getPossibleTransitions();
    int i = 0;
    for (auto &tran : trans) {
        if (i != 0){
            for (int j = 0; j < depth; j++) {
                cout << "         ";
            }
            cout << "| " << "--" << tran->transitionSymbol << "--> ";
        } else {
            if (node->getNodeNumber() < 10){
                cout << node->getNodeNumber() << " " << "--" << tran->transitionSymbol << "--> ";
            } else {
                cout << node->getNodeNumber() << "--" << tran->transitionSymbol << "--> ";
            }
        }
        printRecursive(tran->toNode, depth+1, map1);
        i++;
    }
}
