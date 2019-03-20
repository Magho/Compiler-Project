#include <utility>
#include <iostream>
#include "CombinedNFA.h"

void CombinedNFA::printCombinedNFA() {

    map<int, bool> map1;
    for (int i = 0; i < this->NFAs.size(); ++i) {
        vector<Node*> graph = this->NFAs[i]->getGraphNodes();
        for (int j = 0; j < graph.size() ; ++j) {
            map1.insert(pair<int, bool>(graph[j]->getNodeNumber(), false));
        }
    }

    map1.insert(pair<int, bool>(this->startNode->getNodeNumber(), false));
    printRecursive(this->startNode, 0, &map1);
}

void CombinedNFA::printRecursive(Node* node, int depth, map<int, bool>* map1) {
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