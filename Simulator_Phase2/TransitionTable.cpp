//
// Created by sajed on 20/04/19.
//

#include "TransitionTable.h"

TransitionTable::TransitionTable(vector<ProductionElement*> terminals,
                                 vector<ProductionElement*> nonTerminals,
                                 map<string, vector<ProductionElement>> firstSet,
                                 map<string, vector<ProductionElement>> followSet) {
    this->transitionTable = new Production**[nonTerminals.size()];
    for (int i = 0; i < terminals.size(); i++) {
        this->transitionTable[i] = new Production*[terminals.size()];
    }

    //TODO fill transition table
}

int TransitionTable::getRowIndex(ProductionElement* pe) {

}

int TransitionTable::getColumnIndex(ProductionElement* terminal) {

}

string TransitionTable::getLeftHandSide(int rowIndex) {

}


