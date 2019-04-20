//
// Created by magho on 4/19/19.
//


#ifndef COMPILER2_FIRSTSET_H
#define COMPILER2_FIRSTSET_H

#include <unordered_map>
#include <vector>
#include "../CFG/CFG.h"

class Set {
    public:
        string name;
        Set (string name){
            this->name = name;
        }
        unordered_map<string ,ProductionElement*> SetTerminals;
        unordered_map<string ,Production*> SetTerminalsProductions;
        unordered_map<string ,Set*> SetNonTerminals;
        void finishMyFirstSet (bool isFollow); //call after iterating on all the map of the CFG
};


#endif //COMPILER2_FIRSTSET_H
