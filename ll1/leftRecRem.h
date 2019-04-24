//
// Created by ABDO on 4/19/2019.
//
#include <iostream>
#include <vector>
#include <string>
#include "../CFG/CFG.h"
#include "../CFG/Production.h"
#include "../CFG/ProductionElement.h"
#ifndef COMPILER_PROJECT_LEFTRECREM_H
#define COMPILER_PROJECT_LEFTRECREM_H
class ruleHelper{
public:
    ruleHelper(string s , vector<Production*>* p){
        lhs=s;
        rhs=p;
    }
    void printRule(){
        cout<< lhs <<"---------> ";
        for(Production * p :*rhs) p->printProduction();
    }
    string lhs;
    vector<Production*> * rhs;
};

class leftRecursionRemover{
private:
    vector<ruleHelper*> rules;
    CFG *c ;

    bool directRemoveLR(int index,bool debug);
    bool isLeftRec(int index);

        public:
    vector<ruleHelper*> * getHelper();
    /*
     * the constructor accepts cfg to get rules and modify its rules
     * */
    leftRecursionRemover(CFG *cfg);
    /*returns true in case of the given CFG is not ll1 and it's converted successfully
     * returns false if the CFG is already ll1
     * if debug is true the function will print the steps
     * */
    bool  preformLRR(bool debug);

};
#endif //COMPILER_PROJECT_LEFTRECREM_H
