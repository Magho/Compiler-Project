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
            calcFirstSet();
            calcFollowtSet();
        }
        unordered_map<string, vector<ProductionElement>> firstSet;
        unordered_map<string, vector<ProductionElement>> followSet;
        unordered_map<string, Set*> firstSets;
        unordered_map<string, Set*> followSets;
        void calcFirstSet();
        void calcFollowtSet();
//        map<string, vector<ProductionElement>> getFirsttSet();
//        map<string, vector<ProductionElement>> getFollowtSet();

};

#endif //COMPILER2_FIRSTANDFOLLOWLOGIC_H
