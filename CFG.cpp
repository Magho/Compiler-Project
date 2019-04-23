//
// Created by ecc on 19/04/2019.
//
#include <iostream>
#include <string>
#include "CFG.h"

/*
 * added by abdo ..
 * to preform ll1 directly on the rules
 * don't worry about encapsulation , rules will be fine lol
 * */
unordered_map<string, vector<Production*>*> * CFG::getCFGRules(){
    return &rules;
}



ProductionElement* CFG::createNewTerminal(string symbolValue) {
    if(doesExist(symbolValue, 1)) {
        return getProductionElement(symbolValue, 1);
    }
    if(DEBUG) {
        cout << "Creating new terminal " << symbolValue << "." << endl;
    }
    ProductionElement* newTerminal = new ProductionElement(1, symbolValue);
    terminals.push_back(newTerminal);
    return newTerminal;
}

ProductionElement* CFG::createNewNonTerminal(string symbolValue) {
    if(doesExist(symbolValue, 0)) {
        return getProductionElement(symbolValue, 0);
    }
    if(DEBUG) {
        cout << "Creating new non-terminal " << symbolValue << "." << endl;
    }
    ProductionElement* newNonTerminal = new ProductionElement(0, symbolValue);
    nonTerminals.push_back(newNonTerminal);
    rules[symbolValue] = new vector<Production*>();
    return  newNonTerminal;
}

ProductionElement* CFG::createStartingSymbol(string symbolValue) {
    if(DEBUG) {
        cout << "Creating starting symbol " << symbolValue << "." << endl;
    }
    startingProductionElement = new ProductionElement(0, symbolValue);
    nonTerminals.push_back(startingProductionElement);
    rules[symbolValue] = new vector<Production*>();
    return startingProductionElement;
}

int CFG::doesExist(string symbolValue, int isTerminal) {
    if(DEBUG) {
        cout << "Searching for " << (isTerminal? "the terminal " : "the non-terminal ") << symbolValue << "." << endl;
    }
    if(isTerminal) {
        for(auto i : terminals) {
            if(DEBUG) {
                cout << "Comparing " << symbolValue << " with " << i->getSymbolValue() << endl;
            }
            if(symbolValue == i->getSymbolValue()) {
                return 1;
            }
        }
        return 0;
    } else {
        if(DEBUG) {
            cout << symbolValue <<(rules.count(symbolValue) ? " is found": " isn't found") << endl;
        }
        return (int)rules.count(symbolValue);
    }
}

ProductionElement* CFG::getProductionElement(string symbolValue) {
    cout << "Getting Element " << symbolValue << "..." << endl;
    cout << "Searching in non-terminals..." << endl;
    for(auto i : nonTerminals) {
        if(DEBUG) {
            cout << "Comparing " << symbolValue << " with " << i->getSymbolValue() << endl;
        }
        if(symbolValue == i->getSymbolValue()) {
            return i;
        }
    }
    cout << "Not found in non-terminals, Searching in terminals..." << endl;
    for(auto i : terminals) {
        if(DEBUG) {
            cout << "Comparing " << symbolValue << " with " << i->getSymbolValue() << endl;
        }
        if(symbolValue == i->getSymbolValue()) {
            return i;
        }
    }
    if(DEBUG) {
        cout << symbolValue << "isn't found" << endl;
    }
    return NULL;
}
ProductionElement* CFG::getProductionElement(string symbolValue,int isTerminal) {
    cout << "Getting Element " << symbolValue << "..." << endl;
    if(!isTerminal) {
        for(auto i : nonTerminals) {
            if(DEBUG) {
                cout << "Comparing " << symbolValue << " with " << i->getSymbolValue() << endl;
            }
            if(symbolValue == i->getSymbolValue()) {
                return i;
            }
        }
    } else {
        for(auto i : terminals) {
            if(DEBUG) {
                cout << "Comparing " << symbolValue << " with " << i->getSymbolValue() << endl;
            }
            if(symbolValue == i->getSymbolValue()) {
                return i;
            }
        }
    }
    if(DEBUG) {
        cout << symbolValue << "isn't found" << endl;
    }
    return NULL;
}
void CFG::assignProductionToNonTerminal(Production* p, string nt,int pos) {
    if(DEBUG) {
        cout << "Assigning Production to " << nt << ": ";
        p->debugProduction();
    }
    if(!doesExist(nt, 0)) {
        cout << "ERROR: " << nt << " doesn't exist!!" << endl;
        return;
    }
    vector<Production*>* productions = rules[nt];
    productions->insert(productions->begin()+pos,p);
}
void CFG::assignProductionToNonTerminal(Production* p, string nt) {
    if(DEBUG) {
        cout << "Assigning Production to " << nt << ": ";
        p->debugProduction();
    }
    if(!doesExist(nt, 0)) {
        cout << "ERROR: " << nt << " doesn't exist!!" << endl;
        return;
    }
    vector<Production*>* productions = rules[nt];
    productions->push_back(p);
}
void CFG::debug() {
    if(DEBUG) {
        cout << "Debugging CFG..." << endl;
        cout << "Terminals:" << endl;
        for(auto i : terminals) {
            cout << i->getSymbolValue() << endl;
        }
        cout << "End of terminals..." << endl;
        cout << "Non-terminals:" << endl;
        for(auto i : nonTerminals) {
            cout << i->getSymbolValue() << endl;
        }
        cout << "End of non-terminals..." << endl;
        cout << startingProductionElement->getSymbolValue() << " -> ";
        for(auto i : *rules[startingProductionElement->getSymbolValue()]) {
            i->debugProductionCFG();
            cout << "|";
        }
        cout << endl;
        for(auto i : rules) {
            if(i.first == startingProductionElement->getSymbolValue()) {
                continue;
            }
            cout << i.first << " -> ";
            for(auto j : *i.second) {
                j->debugProductionCFG();
                cout << "|";
            }
            cout << endl;
        }
        cout << "End of CFG...." << endl;
    }
}