#include <iostream>
#include<vector>
#include<string>
#include "NFAtoDFA.h"
#include "Minimization.h"
#include "RulesParser.h"
#include "Converter.h"
#include "Simulator/Simulator.h"
#include "CFG.h"
#include "GrammarParser.h"
#include "Simulator_Phase2/TransitionTable.h"
#include "Simulator_Phase2/PredictiveParser.h"

using namespace std;
int main(){

    // PHASE 1

    RulesParser *rulesParser= new RulesParser();
    unordered_map <string, stack<char>> map = rulesParser->getRegularExpressionPostfixes("input.txt");
    vector<string> labels = rulesParser->getLabelsOrdered();
    Converter conv;
    CombinedNFA combinednfa = conv.regularExpressionToNFA(map,labels);
    NFAtoDFA *cnvrt = new NFAtoDFA(combinednfa.startNode);
    cnvrt->operate();
    vector<Node *> res = cnvrt->getResult();
    Minimization *minimization = new Minimization(&res);
    vector<Node*> v = minimization->getMinimizedTable();

    Simulator* simulator = new Simulator(v);
    simulator->resetInputFile("/home/sajed/CLionProjects/Compilers_Phase1/testInput.txt");
    string nextToken = "";
    simulator->generateTokensFileAndSymbolTable();


    // PHASE 2

//    CFG cfg = * new CFG();
//    GrammarParser gp = * new GrammarParser("/home/sajed/CLionProjects/Compiler_Phase2/grammarInput.txt");
//
//    vector<ProductionElement*> terminals = cfg.terminals;
//    vector<ProductionElement*> nonTerminals = cfg.nonTerminals;
//    ProductionElement* start = cfg.startingProductionElement;
//
//    map<string, vector<ProductionElement>> firstSet;
//    map<string, vector<ProductionElement>> followSet;
//
//    TransitionTable * transitionTable = new TransitionTable(terminals, nonTerminals,
//                                                            firstSet, followSet);
//
//    PredictiveParser pp = * new PredictiveParser(start, transitionTable);
//    pp.generateLeftMostDerivation(simulator);

    return 0;
}
