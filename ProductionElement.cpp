#include <iostream>
#include <string>

#include "ProductionElement.h"
ProductionElement::ProductionElement(int isTerminal, string symbolValue) {
    terminal = isTerminal;
    this->symbolValue = symbolValue;
}

string ProductionElement::getSymbolValue() {
    return symbolValue;
}

int ProductionElement::isTerminal() {
    return  terminal;
}

int ProductionElement::isNonTerminal() {
    return !terminal;
}
void ProductionElement::debug() {
    if(DEBUG) {
        cout << symbolValue << endl;
    }
}

//TODO Magho
bool ProductionElement::hasEpsilon() {
    return gotEpsilon;
}
