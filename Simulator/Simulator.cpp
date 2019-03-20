//
// Created by sajed on 15/03/19.
//

#include <iostream>
#include "Simulator.h"

Simulator::Simulator(vector<Node*> DFATable) {
    this->DFATable = DFATable;
}

bool Simulator::getNextToken(string& nextToken) {

}

void Simulator::resetInputFile(string inputFilePath) {

}

bool Simulator::endOfFile(ifstream &inputFile) {

}

string Simulator::handleErrorTillSeparator(ifstream &inputFile) {

}

string Simulator::handleErrorRemoveChar(ifstream &inputFile) {

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