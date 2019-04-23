//
// Created by sajed on 20/04/19.
//

#include <algorithm>
#include "TransitionTable.h"

TransitionTable::TransitionTable(vector<ProductionElement*> terminals,
                                 vector<ProductionElement*> nonTerminals,
                                 unordered_map<string, Set*> firstSet,
                                 unordered_map<string, Set*> followSet) {
    // Remove epsilon
    terminals.erase(std::remove_if(terminals.begin(), terminals.end(),
                           [](ProductionElement *i) { return i->symbolValue.compare("~") == 0; }), terminals.end());
    // Insert $ if not exist
    bool $exist = false;
    for (int j = 0; j < terminals.size(); ++j) {
        if (terminals[j]->symbolValue.compare("$") == 0) {
            $exist = true;
            break;
        }
    }
    if (!$exist) {
        terminals.push_back(new ProductionElement(true, "$"));
    }

    this->terminals = terminals;
    this->nonTerminals = nonTerminals;

    this->transitionTable = new Production**[nonTerminals.size()];
    for (int i = 0; i < terminals.size(); i++) {
        this->terminalsIndex[terminals[i]->symbolValue] = i;
        this->transitionTable[i] = new Production*[terminals.size()];
    }

    for (int i = 0; i < nonTerminals.size(); i++) {
        this->nonTerminalsIndex[nonTerminals[i]->symbolValue] = i;
        for (int j = 0; j < terminals.size(); j++) {
            transitionTable[i][j] = nullptr;
        }
    }

    for (int i = 0; i < nonTerminals.size(); i++) {
        Set * tempSet = followSet[nonTerminals[i]->getSymbolValue()];
        for (auto j: tempSet->SetTerminals) {
            Production * sync = new Production;
            sync->isSync = true;
            transitionTable[i][terminalsIndex[j.first]] = sync;
        }
    }

    for (int i = 0; i < nonTerminals.size(); i++) {
        Set * tempFirstSet = firstSet[nonTerminals[i]->getSymbolValue()];
        Set * tempFollowSet = followSet[nonTerminals[i]->getSymbolValue()];
        for (auto j: tempFirstSet->SetTerminals) {
            if (j.first.compare("~") == 0) {
                Production * epsilon = new Production;
                epsilon->isEpsilon = true;
                ProductionElement * pe = new ProductionElement(true, "Epsilon");
                epsilon->appendNewProductionElement(pe);
                for (auto k: tempFollowSet->SetTerminals) {
                    transitionTable[i][terminalsIndex[k.first]] = epsilon;
                }
            } else {
                transitionTable[i][terminalsIndex[j.first]] = tempFirstSet->SetTerminalsProductions[j.first];
            }
        }
        cout << endl;
    }




}

int TransitionTable::getRowIndex(ProductionElement* pe) {
    return nonTerminalsIndex.find(pe->symbolValue) != nonTerminalsIndex.end()? nonTerminalsIndex[pe->symbolValue] : -1;
}

int TransitionTable::getColumnIndex(ProductionElement* terminal) {
    return terminalsIndex.find(terminal->symbolValue) != terminalsIndex.end()? terminalsIndex[terminal->symbolValue] : -1;
}

string TransitionTable::getLeftHandSide(int rowIndex) {
    return this->nonTerminals[rowIndex]->getSymbolValue();
}

void TransitionTable::printTransitionTable() {
    cout << endl << endl;
    cout << "";
    for (auto ter: this->terminals)
        printf("\t\t%10s", ter->symbolValue.c_str());
    cout << endl;
    for (int i = 0; i < nonTerminals.size(); ++i) {
        cout << nonTerminals[i]->symbolValue << ":  \t";
        for (int j = 0; j < terminals.size(); ++j) {

            if (this->transitionTable[i][j] != nullptr) {
                if (this->transitionTable[i][j]->isSync) {
                    printf("%10s", "Syn");
                } else if (this->transitionTable[i][j]->isEpsilon) {
                    printf("%10s", "Eps");
                } else {
                    string temp = "";
                    for (auto pe : this->transitionTable[i][j]->productionValue) {
                        temp = temp.append(pe->getSymbolValue());
                    }
                    printf("%10s", temp.c_str());
                }
                cout << "\t\t";
            } else {
                printf("%10s", "Err");
                cout << "\t\t";
            }
        }
        cout << endl;
    }
}



