//
// Created by  on 19/04/2019.
//

#ifndef COMPILERPROJECT_PRODUCTIONELEMENT_H
#define COMPILERPROJECT_PRODUCTIONELEMENT_H
#include <iostream>

using namespace std;
class ProductionElement {
private:
    int DEBUG = 1;
    int terminal = 0;
    string symbolValue;
public:
    ProductionElement(int isTerminal, string symbolValue);
    string getSymbolValue();
    // TODO Magho
    bool isTerminal();
    bool hasEpsilon();//just if non terminal//TODO
    //
    void debug();
};


#endif //COMPILERPROJECT_PRODUCTIONELEMENT_H