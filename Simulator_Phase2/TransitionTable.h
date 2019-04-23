//
// Created by sajed on 20/04/19.
//

#ifndef COMPILER_PHASE2_TRANSITIONTABLE_H
#define COMPILER_PHASE2_TRANSITIONTABLE_H

#include <string>
#include <vector>
#include <map>
#include "../CFG/ProductionElement.h"
#include "../CFG/Production.h"
#include "../FirstAndFollow/Set.h"

using namespace std;

class TransitionTable {
public:
    unordered_map<string, int> terminalsIndex;
    unordered_map<string, int> nonTerminalsIndex;

    Production*** transitionTable;
    TransitionTable(vector<ProductionElement*> terminals,
                    vector<ProductionElement*> nonTerminals,
                    unordered_map<string, Set*> firstSet,
                    unordered_map<string, Set*> followSet);
    int getRowIndex(ProductionElement* pe);
    int getColumnIndex(ProductionElement* terminal);
    string getLeftHandSide(int rowIndex);
    void printTransitionTable();
    vector<ProductionElement*> terminals;
    vector<ProductionElement*> nonTerminals;

};


#endif //COMPILER_PHASE2_TRANSITIONTABLE_H
