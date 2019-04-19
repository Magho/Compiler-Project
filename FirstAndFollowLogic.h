//
// Created by magho on 4/19/19.
//

#ifndef COMPILER2_FIRSTANDFOLLOWLOGIC_H
#define COMPILER2_FIRSTANDFOLLOWLOGIC_H

#include "Set.h"

class FirstAndFollowLogic {
    public:
        CFG *grammer;
        FirstAndFollowLogic(CFG *cfg){
            this->grammer = cfg;
        }
        map<string, vector<ProductionElement>> firstSet;
        map<string, vector<ProductionElement>> followSet;
        map<string, Set*> firstSets;
        map<string, Set*> followSets;
        void calcFirstSet();
        void calcFollowtSet();
        map<string, vector<ProductionElement>> getFirsttSet();
        map<string, vector<ProductionElement>> getFollowtSet();

};

#endif //COMPILER2_FIRSTANDFOLLOWLOGIC_H
