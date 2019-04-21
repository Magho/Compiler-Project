

#ifndef COMPILERPROJECT_PRODUCTIONELEMENT_H
#define COMPILERPROJECT_PRODUCTIONELEMENT_H
#include <iostream>

using namespace std;
class ProductionElement {
public:
    int DEBUG = 0;
    int terminal = 0;
    string symbolValue;

    ProductionElement(int isTerminal, string symbolValue);
    string getSymbolValue();
    int isTerminal();
    int isNonTerminal();
    void debug();
    // TODO Magho
    bool gotEpsilon;
    bool hasEpsilon();//just if non terminal//TODO
};


#endif //COMPILERPROJECT_PRODUCTIONELEMENT_H