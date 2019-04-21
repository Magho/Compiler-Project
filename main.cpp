#include <iostream>
#include<vector>
#include<string>

#include "Simulator/Simulator.h"
#include "CFG.h"
#include "GrammarParser.h"
#include "Simulator_Phase2/TransitionTable.h"
#include "Simulator_Phase2/PredictiveParser.h"
#include "ParsingRules/RulesParser.h"
#include "GeneratingNFA/Converter.h"
#include "MinimizedDFA/NFAtoDFA.h"
#include "MinimizedDFA/Minimization.h"

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
    simulator->generateTokensFileAndSymbolTable();
    return 0;
}
