//
// Created by ABDO on 4/19/2019.
//
#include <iostream>
#include <vector>
#include <string>
#include "../CFG/CFG.h"
#include "../CFG/Production.h"
#include "../CFG/ProductionElement.h"
#include "leftRecRem.h"
#ifndef COMPILER_PROJECT_LEFTFAC_H
#define COMPILER_PROJECT_LEFTFAC_H


class leftFac{
private:
    vector<ruleHelper*> *rules;
    CFG *c ;

public:

    leftFac(CFG *cfg,vector<ruleHelper*> *ruless);
    bool preformLF(bool debug);

};
#endif //COMPILER_PROJECT_LEFTFAC_H
