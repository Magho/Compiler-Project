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
void directRemoveLR(int index){

}
bool  leftRecursionRemover::preformLL1(bool debug){
    int originalSize=rules.size(); // am doing so bcuz i'll add el rules elgdida with pushback op O(1) and i do not want to loop into the new prods FOR NOW
    for(int i=0;i<originalSize;i++){
            for(int k=rules.at(i)->rhs->size()-1;k>=0;k--){
                Production *p = rules.at(i)->rhs->at(k);
                ProductionElement  *e  =p->getProductionVals()->at(0);
                if(e->isNonTerminal()) {
                    for (int j = 0; j < i; j++) {
                        if(rules.at(j)->lhs == e->getSymbolValue()){
                            //remove e from prod, distribute the rest of prod to rules.at j as new prods for each , add these prods to rules at i and remove org prod
                            rules.at(i)->rhs->erase(rules.at(i)->rhs->begin()+k); // remove current prod
                            p->getProductionVals()->erase( p->getProductionVals()->begin() ); // remove first elem
                            for(int x =0;x<rules.at(j)->rhs->size();x++){
                                Production *newP = new Production();
                                for(int z=0;z<rules.at(j)->rhs->at(x)->getProductionVals()->size();z++) {
                                    newP->appendNewProductionElement(rules.at(j)->rhs->at(x)->getProductionVals()->at(z));
                                }
                                for(int z=0;z<p->getProductionVals()->size();z++) {
                                    newP->appendNewProductionElement(p->getProductionVals()->at(z));
                                }
                                rules.at(i)->rhs->push_back(newP);
                            }
                        }
                    }
                }
            }
            directRemoveLR(i);

    }

    return false;
}

unordered_map<string, vector<Production*>*> *leftRecursionRemover::getCFG(){


    return nullptr;
}