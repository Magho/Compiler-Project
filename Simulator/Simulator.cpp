//
// Created by sajed on 15/03/19.
//
#include <fstream>
#include <iostream>
#include "Simulator.h"

Simulator::Simulator(vector<Node*> DFATable) {
    this->DFATable = DFATable;
    fixDFATableToIgnoreSpaces(this->DFATable);
    this->currentNode = DFATable[0];
    this->dummyNode = DFATable[DFATable.size() - 1];
}

bool Simulator::getNextToken(string& nextToken) {
    ifstream inputFile = ifstream(this->inputFilePath);     // open file
    if (posOfCursor == -1) {
        inputFile.seekg(0, ios::end);
    } else {
        inputFile.seekg(this->posOfCursor);
    }
    if (endOfFile(inputFile)) {
        return false;
    }
    this->currentNode = this->DFATable[0];
    this->posOflastInputToChangeStartState = 0;
    this->maximalMunchAcceptedToken = "";
    this->maximalMunchAcceptedLexeme = "";
    while (inputFile.get(this->c)) {         // loop getting single characters

        Node* nextNode = this->currentNode->getPossibleTransitions()[c]->toNode;
        if (nextNode->isFinal()) {
            this->maximalMunchAcceptedToken = nextNode->getTokenName();
            this->posOfAcceptedToken = inputFile.tellg();
            this->panicMode = false;
        }
        if (currentNode->isStart() and !nextNode->isStart()) {
            posOflastInputToChangeStartState = inputFile.tellg();
        }

        if (nextNode == dummyNode) {
            if (!this->maximalMunchAcceptedToken.empty()) { // An accepted token found
                this->posOfCursor = this->posOfAcceptedToken;
                nextToken = this->maximalMunchAcceptedToken;
                this->maximalMunchAcceptedToken = "";
                inputFile.close();                // close file
                return true;
            } else {                                    // No tokens found
                string errMsg = handleErrorRemoveChar(inputFile);
                if (!errMsg.empty()) {
                    this->posOfCursor = inputFile.tellg();
                    nextToken = errMsg;
                    inputFile.close();                // close file
                    return true;
                }
            }
        } else {

            this->maximalMunchAcceptedLexeme += c;
            this->posOfCursor = inputFile.tellg();
            this->currentNode = nextNode;
        }
        if (endOfFile(inputFile)) {

            if (!this->maximalMunchAcceptedToken.empty()) { // An accepted token found
                nextToken = this->maximalMunchAcceptedToken;
                this->maximalMunchAcceptedToken = "";
                this->posOfCursor = posOfAcceptedToken;
                inputFile.close();                // close file
                return true;
            } else if (currentNode->isStart() or panicMode) {                                    // No tokens found
                string errMsg = handleErrorRemoveChar(inputFile);
                nextToken = errMsg;
                this->posOfCursor = inputFile.tellg();
                inputFile.close();                // close file
                return false;
            } else {
                string errMsg = handleErrorRemoveChar(inputFile);
                nextToken = errMsg;
                this->posOfCursor = inputFile.tellg();
                inputFile.close();                // close file
                return true;
            }
        }
    }
}

void Simulator::resetInputFile(string inputFilePath) {
    this->inputFilePath = inputFilePath;
    this->maximalMunchAcceptedToken = "";
    this->posOfAcceptedToken = 0;
    this->posOfCursor = 0;
    this->posOflastInputToChangeStartState = 0;
    this->panicMode = false;
}

bool Simulator::endOfFile(ifstream &inputFile) {
    if (inputFile.peek() == EOF) {
        if (inputFile.eof())
            return true;
    }
    return false;
}

string Simulator::handleErrorTillSeparator(ifstream &inputFile) {
    while (this->c != ' ' and this->c != '\t' and this->c != '\n' and inputFile.get(this->c));
    return "Undefined token";
}

string Simulator::handleErrorRemoveChar(ifstream &inputFile) {
    string errMsg = this->panicMode? "" : "Undefined token";
    inputFile.seekg(posOflastInputToChangeStartState++);
    this->panicMode = true;
    this->currentNode = this->DFATable[0];
    this->maximalMunchAcceptedLexeme = "";
    return errMsg;
}

void Simulator::fixDFATableToIgnoreSpaces(vector<Node*> DFATable) {
    Node* dummyNode = this->DFATable[DFATable.size() - 1];
    Node* startNode = this->DFATable[0];
    this->DFATable[0]->editTransition(startNode, ' ');
    this->DFATable[0]->editTransition(startNode, '\t');
    this->DFATable[0]->editTransition(startNode, '\n');
    for (int i = 1; i < DFATable.size(); i++) {
        this->DFATable[i]->editTransition(dummyNode, ' ');
        this->DFATable[i]->editTransition(dummyNode, '\t');
        this->DFATable[i]->editTransition(dummyNode, '\n');
    }
}

void Simulator::generateTokensFileAndSymbolTable() {
    string nextToken = "";
    ofstream outputFile;
    outputFile.open ("/home/sajed/CLionProjects/Compiler_Phase2/Tokens.txt");
    ofstream symbolTable;
    symbolTable.open ("/home/sajed/CLionProjects/Compiler_Phase2/SymbolTable.txt");
    while (this->getNextToken(nextToken)) {
        outputFile << nextToken << endl;
        if (nextToken.compare("Id") == 0) {
            symbolTable << this->maximalMunchAcceptedLexeme << endl;
            cout << this->maximalMunchAcceptedLexeme << endl;
        }
    }
    symbolTable.close();
    outputFile.close();
}
