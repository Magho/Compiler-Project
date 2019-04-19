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


/*
 - Arrange non-terminals in some order: A1
 ... An
- for i from 1 to n do {
- for j from 1 to i-1 do {
replace each production
Ai  Aj

 by
Ai  1
 | ... | k

where Aj  1
 | ... | k
 }
- eliminate immediate left-recursions among Ai
 productions
}
 * */

bool  leftRecursionRemover::preformLL1(bool debug){
    for(int i=0;i<rules.size();i++){
            for(int k=0;k<rules.at(i)->rhs->size();k++){
                if(rules.at(i)->rhs->at(k))
                for(int j=0;j<i;j++){

                }
        }
    }

    return false;
}

unordered_map<string, vector<Production*>*> *leftRecursionRemover::getCFG(){


    return nullptr;
}