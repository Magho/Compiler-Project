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
    for(auto & it:*cfg->getCFGRules()){
        ruleHelper * rh = new ruleHelper(it.first,it.second);
        rules.push_back(rh);
    }

}


bool leftRecursionRemover::isLeftRec(int index){
    for(int i=0;i<rules.at(index)->rhs->size();i++) {
        if(rules.at(index)->rhs->at(i)->getProductionVals()->at(0)->getSymbolValue()==rules.at(index)->lhs)
            return true;
        }
    return false;
}
bool leftRecursionRemover::directRemoveLR(int index){
        string newPotentialName =rules.at(index)->lhs+'`';
        vector<Production*> prods ;
        if(!isLeftRec(index)){
            return false;
        }
        ProductionElement * newElem =c->createNewNonTerminal(newPotentialName);
        for(int i=0;i<rules.at(index)->rhs->size();i++){
            if(rules.at(index)->rhs->at(i)->getProductionVals()->at(0)->getSymbolValue()==rules.at(index)->lhs){
                Production *p = new Production();
                int size = rules.at(index)->rhs->at(i)->getProductionVals()->size();
                if(size==1){
                    cout<<"error .. A->A can't be turned to ll (1)";
                    return;
                }
                for(int k=1;k<size;k++){
                    p->appendNewProductionElement(rules.at(index)->rhs->at(i)->getProductionVals()->at(k));
                }
                p->appendNewProductionElement(newElem);
                prods.push_back(p);
                c->assignProductionToNonTerminal(p,newPotentialName); //TODO
                rules.at(index)->rhs->erase(rules.at(index)->rhs->begin()+i);
            }else{
                rules.at(index)->rhs->at(i)->getProductionVals()->push_back(newElem);
            }
        }
        Production * epsProd = new Production();
        epsProd->appendNewProductionElement(c->createNewTerminal("\\L"));
        c->assignProductionToNonTerminal(epsProd,newPotentialName); //TODO
        prods.push_back(epsProd);
        ruleHelper * newRule = new ruleHelper(newPotentialName,&prods);
        rules.push_back(newRule);
        return true;
}
bool  leftRecursionRemover::preformLL1(bool debug){
    if(debug){
        cout<<"hello and welcome to the bounce part \n let's clean  this CFG from left recursion...\n";
    }
    bool notLL1=false;
    int originalSize=rules.size(); // am doing so bcuz i'll add el rules elgdida with pushback op O(1) and i do not want to loop into the new prods FOR NOW
    for(int i=0;i<originalSize;i++){
        if(debug){
            cout<<"loop no"<<i<<" in rules-------------------------------------------\n";
        }
            for(int k=rules.at(i)->rhs->size()-1;k>=0;k--){

                Production *p = rules.at(i)->rhs->at(k);
                ProductionElement  *e  =p->getProductionVals()->at(0);
                if(debug){
                    cout<<"looking at production no "<<k<< " which is "<<p->printProduction();
                }
                if(e->isNonTerminal()) {
                    for (int j = 0; j < i; j++) {
                        if(rules.at(j)->lhs == e->getSymbolValue()){
                            //remove e from prod, distribute the rest of prod to rules.at j as new prods for each , add these prods to rules at i and remove org prod
                            rules.at(i)->rhs->erase(rules.at(i)->rhs->begin()+k); // remove current prod
                            p->getProductionVals()->erase( p->getProductionVals()->begin() ); // remove first elem from the prod
                            for(int x =0;x<rules.at(j)->rhs->size();x++){         //for each elem in rhs of j
                                Production *newP = new Production();
                                c->assignProductionToNonTerminal(newP,rules.at(i)->lhs );
                                for(int z=0;z<rules.at(j)->rhs->at(x)->getProductionVals()->size();z++) {   //add j's elems
                                    newP->appendNewProductionElement(rules.at(j)->rhs->at(x)->getProductionVals()->at(z));
                                }
                                for(int z=0;z<p->getProductionVals()->size();z++) {                         //then add the removed prod elems
                                    newP->appendNewProductionElement(p->getProductionVals()->at(z));
                                }
                                rules.at(i)->rhs->push_back(newP);                                          // then add A'
                            }
                        }
                    }
                }
            }
            notLL1 = notLL1||directRemoveLR(i);
    }

    return notLL1;
}

