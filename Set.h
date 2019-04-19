//
// Created by magho on 4/19/19.
//


#ifndef COMPILER2_FIRSTSET_H
#define COMPILER2_FIRSTSET_H

#include <map>
#include <vector>
#include "CFG.h"

class Set {
    public:
        map<string ,ProductionElement*> SetTerminals;
        map<string ,Set*> SetNonTerminals;
        void finishMyFirstSet (bool isFollow); //call after iterating on all the map of the CFG
};


#endif //COMPILER2_FIRSTSET_H
