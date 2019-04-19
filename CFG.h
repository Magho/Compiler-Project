//
// Created by ecc on 19/04/2019.
//

#ifndef COMPILERPROJECT_CFG_H
#define COMPILERPROJECT_CFG_H
#include <unordered_map>
#include "Production.h"
/*To get familiar with CFG put code below in main:
    CFG grammar;
    ProductionElement* startingSymbol = grammar.createStartingSymbol("Method_Body");
    ProductionElement* nonTerminal = grammar.createNewNonTerminal("STATEMENT_LIST");
    ProductionElement* terminal = grammar.createNewTerminal("a");
    Production* production1 = new Production();
    production1->appendNewProductionElement(terminal);
    production1->appendNewProductionElement(nonTerminal);
    grammar.assignProductionToNonTerminal(production1, startingSymbol->getSymbolValue());
    Production* production2 = new Production();
    production2->appendNewProductionElement(terminal);
    grammar.assignProductionToNonTerminal(production2, nonTerminal->getSymbolValue());
    grammar.assignProductionToNonTerminal(production2, startingSymbol->getSymbolValue());
    grammar.debug();
 */
class CFG {
private:
    int DEBUG = 0;
    unordered_map<string, vector<Production*>*> rules;
    vector<ProductionElement*> terminals;
    vector<ProductionElement*> nonTerminals;
    ProductionElement* startingProductionElement;
public:
    unordered_map<string, vector<Production*>*> *getCFGRules();
    ProductionElement* createNewTerminal(string symbolValue);
    ProductionElement* createNewNonTerminal(string symbolValue);
    ProductionElement* createStartingSymbol(string symbolValue);
    int doesExist(string symbolValue, int isTerminal);
    ProductionElement* getProductionElement(string symbolValue);
    ProductionElement* getProductionElement(string symbolValue, int isTerminal);
    void assignProductionToNonTerminal(Production* p, string nt,int pos);
    void debug();
};


#endif //COMPILERPROJECT_CFG_H
