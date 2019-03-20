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

}