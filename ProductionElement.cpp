//
// Created by ecc on 19/04/2019.
//

#include "ProductionElement.h"
ProductionElement::ProductionElement(int isTerminal, string symbolValue) {
    terminal = isTerminal;
    this->symbolValue = symbolValue;
}

string ProductionElement::getSymbolValue() {
    return symbolValue;
}

bool ProductionElement::isTerminal() {
    return terminal != 0;
}

void ProductionElement::debug() {
    if(DEBUG) {
        cout << symbolValue << endl;
    }
}

//TODO
bool ProductionElement::hasEpsilon() {
    return true;
}
