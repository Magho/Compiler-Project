//
// Created by sajed on 15/03/19.
//
#ifndef COMPILERS_PHASE1_SIMULATOR_H
#define COMPILERS_PHASE1_SIMULATOR_H

#include <vector>
#include <fstream>
#include "../GeneratingNFA/Node.h"

using namespace std;

class Simulator {
private:
    vector<Node*> DFATable;
    Node* currentNode;
    Node* dummyNode;
    string inputFilePath = "";
    char c; // currentCharAtFileScanner
    string maximalMunchAcceptedToken = "";
    string maximalMunchAcceptedLexeme = "";
    long posOfAcceptedToken;
    long posOfCursor;
    long posOflastInputToChangeStartState;
    bool panicMode;

    void fixDFATableToIgnoreSpaces(vector<Node*> DFATable);
    string handleErrorTillSeparator(ifstream &inputFile);
    string handleErrorRemoveChar(ifstream &inputFile);
    bool endOfFile(ifstream &inputFile);
public:
    Simulator(vector<Node*> DFATable);
    bool getNextToken(string& nextToken);
    void resetInputFile(string inputFilePath);
    void generateTokensFileAndSymbolTable();
};


#endif //COMPILERS_PHASE1_SIMULATOR_H
