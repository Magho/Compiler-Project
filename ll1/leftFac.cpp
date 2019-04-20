//
// Created by ABDO on 4/19/2019.
//
#include "leftFac.h"
leftFac::leftFac(CFG *cfg,    vector<ruleHelper*> *ruless){
    rules = ruless;
    c= cfg;
}
bool leftFac::preformLF(bool debug){
    for(int i=0;i<rules->size();i++){
        if(debug){
            cout<<"------------new RULE ----> \n";
            rules->at(i)->printRule();
        }
        for(int j=0;j<rules->at(i)->rhs->size();j++){

            bool entered= true;
            while (entered){
                if(debug){
                    cout<<"------------base production: \n";rules->at(i)->rhs->at(j)->printProduction();
                }
                entered=false;
            int maxFac=0;
            vector<int> *prodsWithMaxFac=new vector<int>();
                prodsWithMaxFac->push_back(j);
                for(int l=j+1;l<rules->at(i)->rhs->size();l++){
                int num =0;
                while(num<rules->at(i)->rhs->at(j)->getProductionVals()->size()&&num<rules->at(i)->rhs->at(l)->getProductionVals()->size()
                       && rules->at(i)->rhs->at(j)->getProductionVals()->at(num)->getSymbolValue()
                        ==rules->at(i)->rhs->at(l)->getProductionVals()->at(num)->getSymbolValue()){
                    num++;
                }
                if(num>maxFac){
                    maxFac=num;
                    prodsWithMaxFac=new vector<int>();
                    prodsWithMaxFac->push_back(j);
                    prodsWithMaxFac->push_back(l);
                }else if(num==maxFac){
                    prodsWithMaxFac->push_back(l);
                }

            }
                if(debug){
                    cout<<"-----------maxFac"<<maxFac<<endl;
                }
            if(maxFac!=0) {
                entered=true;
                string newName = rules->at(i)->lhs;
                while (c->doesExist(newName, 0)) {
                    newName = newName + "'";
                }
                ProductionElement *e = c->createNewNonTerminal(newName);
                vector<Production*>*ps = new vector<Production*>();
                for (int x = 0; x < prodsWithMaxFac->size(); x++) {
                    Production *p = new Production();
                    Production *t = rules->at(i)->rhs->at(prodsWithMaxFac->at(x));
                    for (int z = maxFac; z < t->getProductionVals()->size(); z++) {
                        p->appendNewProductionElement(t->getProductionVals()->at(z));
                    }
                    if (maxFac == t->getProductionVals()->size()) {
                        p->appendNewProductionElement(c->getProductionElement("\\L"));
                        c->assignProductionToNonTerminal(p, newName);
                    } else {
                        c->assignProductionToNonTerminal(p, newName);
                    }
                    ps->push_back(p);

                }
                ruleHelper * newRule = new ruleHelper(newName,ps);
                rules->push_back(newRule);
                for(int v=0;maxFac+v<rules->at(i)->rhs->at(prodsWithMaxFac->at(0))->getProductionVals()->size();v++) {
                    rules->at(i)->rhs->at(prodsWithMaxFac->at(0))->getProductionVals()->erase(
                            rules->at(i)->rhs->at(prodsWithMaxFac->at(0))->getProductionVals()->begin() +
                            maxFac + v);
                }
                rules->at(i)->rhs->at(prodsWithMaxFac->at(0))->getProductionVals()->push_back(e);
                for (int x = 1; x < prodsWithMaxFac->size(); x++) {
                    rules->at(i)->rhs->erase(rules->at(i)->rhs->begin() + prodsWithMaxFac->at(x) - x);
                }
            }
                }
        }
    }
    if(debug){
        rules->clear();
        for(auto & it:*c->getCFGRules()){
            ruleHelper * rh = new ruleHelper(it.first,it.second);
            rules->push_back(rh);
        }
        cout<<"AND FINALLT that's the result\n BATTLE CONTROL TERMINATED..\n";
        for(ruleHelper*r: *rules){
            r->printRule();
        }
    }

return true;
}
