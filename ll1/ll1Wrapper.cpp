//
// Created by ABDO on 4/19/2019.
//

#ifndef COMPILER_PROJECT_LL1WRAPPER_H
#define COMPILER_PROJECT_LL1WRAPPER_H

#include "leftRecRem.h"
#include "leftFac.h"

int main(){
    CFG * test = new CFG();
  /*  A --> abB | aB | cdg | cdeB | cdfB*/
    test->createNewTerminal("a");
    test->createNewTerminal("b");
    test->createNewTerminal("c");
    test->createNewTerminal("d");
    test->createNewTerminal("e");
    test->createNewTerminal("f");
    test->createNewTerminal("g");
    test->createNewNonTerminal("B");
    test->createStartingSymbol("A");
    Production *p1 =new Production();
    Production *p2 =new Production();
    Production *p3 =new Production();
    Production *p4 =new Production();
    Production *p5 =new Production();
    Production *p6 =new Production();

    p1->appendNewProductionElement(new ProductionElement(1,"a"));
    p1->appendNewProductionElement(new ProductionElement(1,"b"));
    p1->appendNewProductionElement(new ProductionElement(0,"B"));
    p2->appendNewProductionElement(new ProductionElement(1,"a"));
    p2->appendNewProductionElement(new ProductionElement(0,"B"));
    p3->appendNewProductionElement(new ProductionElement(1,"c"));
    p3->appendNewProductionElement(new ProductionElement(1,"d"));
    p3->appendNewProductionElement(new ProductionElement(1,"g"));
    p4->appendNewProductionElement(new ProductionElement(1,"c"));
    p4->appendNewProductionElement(new ProductionElement(1,"d"));
    p4->appendNewProductionElement(new ProductionElement(1,"e"));
    p4->appendNewProductionElement(new ProductionElement(0,"B"));
    p5->appendNewProductionElement(new ProductionElement(1,"c"));
    p5->appendNewProductionElement(new ProductionElement(1,"d"));
    p5->appendNewProductionElement(new ProductionElement(1,"f"));
    p5->appendNewProductionElement(new ProductionElement(0,"B"));
    p6->appendNewProductionElement(new ProductionElement(1,"\\L"));

    test->assignProductionToNonTerminal(p1,"A");
    test->assignProductionToNonTerminal(p2,"A");
    test->assignProductionToNonTerminal(p3,"A");
    test->assignProductionToNonTerminal(p4,"A");
    test->assignProductionToNonTerminal(p5,"A");
    test->assignProductionToNonTerminal(p6,"B");

/*
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
*/



    leftRecursionRemover* lrr = new  leftRecursionRemover(test);
    lrr->preformLRR(false);
    leftFac * lf = new leftFac(test,lrr->getHelper());
    lf->preformLF(true);
    return 0;
};



#endif //COMPILER_PROJECT_LL1WRAPPER_H
