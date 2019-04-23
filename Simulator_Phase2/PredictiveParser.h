//
// Created by sajed on 20/04/19.
//

#ifndef COMPILER_PHASE2_PREDICTIVEPARSER_H
#define COMPILER_PHASE2_PREDICTIVEPARSER_H

#include <stack>
#include "../CFG/ProductionElement.h"
#include "../Simulator/Simulator.h"
#include "../CFG/Production.h"
#include "TransitionTable.h"
#include <fstream>


class PredictiveParser {
public:
    TransitionTable * transitionTable;
    vector<ProductionElement*> stk;
    PredictiveParser(ProductionElement* start, TransitionTable * tb);
    void getIntoPanicMode();
    void generateLeftMostDerivation(Simulator * simulator);

};


#endif //COMPILER_PHASE2_PREDICTIVEPARSER_H
