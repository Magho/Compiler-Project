//
// Created by  on 19/04/2019.
//

#ifndef COMPILERPROJECT_PRODUCTIONELEMENT_H
#define COMPILERPROJECT_PRODUCTIONELEMENT_H
#include <iostream>

using namespace std;
class ProductionElement {
public:
    int DEBUG = 1;
    int terminal = 0;
    string symbolValue;

    ProductionElement(int isTerminal, string symbolValue);
    string getSymbolValue();
    int isTerminal();
    int isNonTerminal();
    void debug();
};


#endif //COMPILERPROJECT_PRODUCTIONELEMENT_H
