#include <iostream>
#include<vector>
#include<string>
#include "NFAtoDFA.h"
#include "Minimization.h"
#include "RulesParser.h"
#include "Converter.h"
#include "Simulator/Simulator.h"

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
    simulator->resetInputFile("/home/magho/workspaceC++/compilerProg/testInput.txt");
    string nextToken = "";
    simulator->generateTokensFileAndSymbolTable();
    return 0;
}
