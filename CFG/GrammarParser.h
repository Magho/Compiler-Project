//
// Created by ecc on 19/04/2019.
//

#ifndef COMPILERPROJECT_GRAMMERPARSER_H
#define COMPILERPROJECT_GRAMMERPARSER_H
#include <fstream>
#include "CFG.h"
#define EPSILON "\L"
class GrammarParser {
private:
    int DEBUG = 0;
    int startingDetected = 0;
    CFG grammar;
public:
    GrammarParser(string inputFile);
    CFG getGrammar();

private:
    string getStringUntil(string &str, string x);
    string trim(string &str, string deli);
    Production* handleProductionString(string p);
};


#endif //COMPILERPROJECT_GRAMMERPARSER_H