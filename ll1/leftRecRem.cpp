//
// Created by ABDO on 4/19/2019.
//
#include "leftRecRem.h"
using namespace std;
leftRecursionRemover::leftRecursionRemover(CFG *cfg){
    //keep the cfg to later use
    c=cfg;
    //pushing the elements from the unordered map to a vector
    //to get consistent iterating process after inserting new elements
    for(auto & it:*cfg.getCFGRules()){
        ruleHelper * rh = new ruleHelper(it.first,it.second);
        rules.push_back(rh);
    }

}




bool  leftRecursionRemover::preformLL1(bool debug){


    return false;
}

unordered_map<string, vector<Production*>*> *leftRecursionRemover::getCFG(){


    return nullptr;
}