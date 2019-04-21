#include <iostream>
#include<vector>
#include<string>

#include "Simulator/Simulator.h"
#include "CFG/CFG.h"
#include "CFG/GrammarParser.h"
#include "Simulator_Phase2/TransitionTable.h"
#include "Simulator_Phase2/PredictiveParser.h"
#include "ParsingRules/RulesParser.h"
#include "GeneratingNFA/Converter.h"
#include "MinimizedDFA/NFAtoDFA.h"
#include "MinimizedDFA/Minimization.h"
#include "FirstAndFollow/FirstAndFollowLogic.h"
#include "CFG/ProductionElement.h"

using namespace std;
int main(){
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
//    simulator->generateTokensFileAndSymbolTable();

     //PHASE 2

    CFG * cfg = new CFG();
    GrammarParser * gp = new GrammarParser("/home/sajed/CLionProjects/Compiler_Phase2/grammarInput.txt");

    vector<ProductionElement*> terminals = cfg->terminals;
    vector<ProductionElement*> nonTerminals = cfg->nonTerminals;
    ProductionElement* start = cfg->startingProductionElement;

//    FirstAndFollowLogic * firstAndFollowLogic = new FirstAndFollowLogic(cfg);
//    unordered_map<string, Set*> firstSet = firstAndFollowLogic->firstSets;
//    unordered_map<string, Set*> followSet = firstAndFollowLogic->firstSets;

    cout << endl << "==========================================" << endl;
    cout << terminals.size();
//    for (int i = 0; i < terminals.size() - 1; i++) {
//        cout << terminals[i]->isTerminal() << " : " << terminals[i]->symbolValue << endl;
//    }
//
//    for (int i = 0; i < nonTerminals.size() - 1; i++) {
//        cout << nonTerminals[i]->isTerminal() << " : " << nonTerminals[i]->symbolValue << endl;
//    }

//    TransitionTable * transitionTable = new TransitionTable(terminals, nonTerminals,
//                                                            firstSet, followSet);
//
//    PredictiveParser pp = * new PredictiveParser(start, transitionTable);
//    pp.generateLeftMostDerivation(simulator);


    return 0;
}


