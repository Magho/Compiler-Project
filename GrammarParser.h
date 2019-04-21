//
// Created by ecc on 19/04/2019.
//

#ifndef COMPILERPROJECT_GRAMMERPARSER_H
#define COMPILERPROJECT_GRAMMERPARSER_H
#include <fstream>
#include "CFG.h"
#define CFGEPSILON "\\L"
class GrammarParser {
private:
    int DEBUG = 1;
    int startingDetected = 0;
    CFG grammar;
public:
    GrammarParser(string inputFile);
    CFG getGrammar();

private:
    string getStringUntil(string &str, string x);
    string trim(string &str, string deli);
    Production* handleProductionString(string p);
    void handleEpsilonProduction(Production *p, string nonTerminal);
};


#endif //COMPILERPROJECT_GRAMMERPARSER_H
