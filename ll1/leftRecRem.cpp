//
// Created by ABDO on 4/19/2019.
//
#include "leftRecRem.h"



int main(){
    CFG * test = new CFG();
    test->createNewTerminal("a");
    test->createNewTerminal("b");
    test->createNewTerminal("c");
    test->createNewTerminal("d");
    test->createNewTerminal("f");
    test->createNewNonTerminal("A");
    test->createStartingSymbol("S");
    Production *p1 =new Production();
    Production *p2 =new Production();
    Production *p3 =new Production();
    Production *p4 =new Production();
    Production *p5 =new Production();

    p1->appendNewProductionElement(new ProductionElement(0,"A"));
    p1->appendNewProductionElement(new ProductionElement(1,"a"));
    p2->appendNewProductionElement(new ProductionElement(1,"b"));
    p3->appendNewProductionElement(new ProductionElement(0,"A"));
    p3->appendNewProductionElement(new ProductionElement(1,"c"));
    p4->appendNewProductionElement(new ProductionElement(0,"S"));
    p4->appendNewProductionElement(new ProductionElement(1,"d"));
    p5->appendNewProductionElement(new ProductionElement(1,"f"));

    test->assignProductionToNonTerminal(p1,"S");
    test->assignProductionToNonTerminal(p2,"S");
    test->assignProductionToNonTerminal(p3,"A");
    test->assignProductionToNonTerminal(p4,"A");
    test->assignProductionToNonTerminal(p5,"A");




    leftRecursionRemover* lrr = new  leftRecursionRemover(test);
    lrr->preformLRR(true);

    return 0;
};
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
bool leftRecursionRemover::directRemoveLR(int index,bool debug){
        string newPotentialName =rules.at(index)->lhs+'`';
        vector<Production*> *prods = new vector<Production*>();
    if(debug) {
        cout << "let's see if we can find any left recusion here in in index "<<index<<endl;
    }
        if(!isLeftRec(index)){
            if(debug) {
                cout << "Nooo getting out of here\n";
            }
            return false;
        }
    if(debug) {
        cout << "there is some here :) ";
        rules.at(index)->printRule();
        cout<<"CREATING THE DASH ELEM "<<newPotentialName<<"\n";
    }

        ProductionElement * newElem =c->createNewNonTerminal(newPotentialName);
        for(int i=0;i<rules.at(index)->rhs->size();i++){
            if(rules.at(index)->rhs->at(i)->getProductionVals()->at(0)->getSymbolValue()==rules.at(index)->lhs){
                Production *p = new Production();
                int size = rules.at(index)->rhs->at(i)->getProductionVals()->size();
                if(size==1){
                    cout<<"error .. A->A can't be turned to ll (1)";
                    return false;
                }
                for(int k=1;k<size;k++){
                    p->appendNewProductionElement(rules.at(index)->rhs->at(i)->getProductionVals()->at(k));
                }
                p->appendNewProductionElement(newElem);
                prods->push_back(p);
                c->assignProductionToNonTerminal(p,newPotentialName); //TODO
                rules.at(index)->rhs->erase(rules.at(index)->rhs->begin()+i);
                i--;
            }else{
                rules.at(index)->rhs->at(i)->getProductionVals()->push_back(newElem);
            }
        }
        Production * epsProd = new Production();
        epsProd->appendNewProductionElement(c->createNewTerminal("\\L"));
        c->assignProductionToNonTerminal(epsProd,newPotentialName); //TODO
        prods->push_back(epsProd);
        ruleHelper * newRule = new ruleHelper(newPotentialName,prods);
        rules.push_back(newRule);
    if(debug) {
        cout << "lets print the old and new rules\n";
        cout<< rules.at(index)->lhs <<"---------> ";
        for(Production * p :*rules.at(index)->rhs) p->printProduction();
        cout<< newRule->lhs <<"---------> ";
       for(Production * p :*newRule->rhs) p->printProduction();

    }
        return true;
}
bool  leftRecursionRemover::preformLRR(bool debug){

    if(debug){
        cout<<"hello and welcome to the bounce part \n let's clean  this CFG from left recursion...\n that's what i recieved\n";
        for(ruleHelper*r: rules){
            r->printRule();
        }
    }
    bool notLL1=false;
    int originalSize=rules.size(); // am doing so bcuz i'll add el rules elgdida with pushback op O(1) and i do not want to loop into the new prods FOR NOW
    for(int i=0;i<originalSize;i++){
        if(debug){
            cout<<"loop no"<<i<<" in rules-------------------------------------------\n";
        }

            for(int k=0;k<rules.at(i)->rhs->size()-1;k++){

                Production *p = rules.at(i)->rhs->at(k);
                ProductionElement  *e  =p->getProductionVals()->at(0);
                if(debug){
                    cout<<"looking at production no "<<k<< " which is ";
                    p->printProduction();
                    cout<<"it's veeeery obvious that first elemnt "<<e->getSymbolValue()<<
                    " is "<<(e->isNonTerminal() ? "nonTerminal\n" : "Terminal\n");
                }
                if(e->isNonTerminal()) {
                    if(debug) {
                        cout << "so we loop in the previous rules to substitute in current nonterminal\n";
                    }
                    for (int j = 0; j < i; j++) {
                        if(rules.at(j)->lhs == e->getSymbolValue()){
                            if(debug) {
                                cout << "WOOOOW at rule number "<<j<<"the LHS is the same as the nonTerminal\n lets sub\n";
                            }
                            //remove e from prod, distribute the rest of prod to rules.at j as new prods for each , add these prods to rules at i and remove org prod
                            rules.at(i)->rhs->erase(rules.at(i)->rhs->begin()+k); // remove current prod
                            p->getProductionVals()->erase( p->getProductionVals()->begin() ); // remove first elem from the prod
                            if(debug) {
                                cout << "old production is removed XxDANGEROUSxX which is \n";p->printProduction();
                            }
                            int OSize=rules.at(j)->rhs->size();
                            for(int x =0;x<OSize;x++){         //for each elem in rhs of j
                                Production *newP = new Production();
                                c->assignProductionToNonTerminal(newP,rules.at(i)->lhs,k+x );
                                for(int z=0;z<rules.at(j)->rhs->at(x)->getProductionVals()->size();z++) {   //add jth xth() elems
                                    newP->appendNewProductionElement(rules.at(j)->rhs->at(x)->getProductionVals()->at(z));
                                }
                                for(int z=0;z<p->getProductionVals()->size();z++) {                         //then add the removed prod elems
                                    newP->appendNewProductionElement(p->getProductionVals()->at(z));
                                }
                                if(debug) {
                                    cout << " this prod is added  TO the rule\n";
                                    newP->printProduction();
                                }
                                cout<<i<<"i "<<k<<"k "<<j<<"j "<<x<<"x--------------------------------------------\n";
                                rules.at(i)->rhs->push_back(newP);
                            }
                            break;
                        }
                    }
                }
            }

            bool t=directRemoveLR(i,debug);
            notLL1 = notLL1||t;
    }

    if(debug){
        cout<<"AND FINALLT that's the result\n BATTLE CONTROL TERMINATED..\n";
        for(ruleHelper*r: rules){
            r->printRule();
        }
    }

    return notLL1;
}

