//
// Created by sajed on 20/04/19.
//

#ifndef COMPILER_PHASE2_TRANSITIONTABLE_H
#define COMPILER_PHASE2_TRANSITIONTABLE_H

#include <string>
#include <vector>
#include <map>
#include "../ProductionElement.h"
#include "../Production.h"

using namespace std;

class TransitionTable {

public:
    Production*** transitionTable;
    TransitionTable(vector<ProductionElement*> terminals,
                    vector<ProductionElement*> nonTerminals,
                    map<string, vector<ProductionElement>> firstSet,
                    map<string, vector<ProductionElement>> followSet);
    int getRowIndex(ProductionElement* pe);
    int getColumnIndex(ProductionElement* terminal);
    string getLeftHandSide(int rowIndex);

};


#endif //COMPILER_PHASE2_TRANSITIONTABLE_H
