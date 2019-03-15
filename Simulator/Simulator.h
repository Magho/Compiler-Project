//
// Created by sajed on 15/03/19.
//
#ifndef COMPILERS_PHASE1_SIMULATOR_H
#define COMPILERS_PHASE1_SIMULATOR_H

#include <vector>
#include "../Transition.h"

using namespace std;

class Simulator {
public:
    vector<Node> DFATable;

    Simulator(vector<Node> DFATable);
    void getNextToken();
    void generateTokensFile();
};


#endif //COMPILERS_PHASE1_SIMULATOR_H
