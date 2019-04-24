
#include <iostream>
#include "FirstAndFollow/FirstAndFollowLogic.h"
#include "Simulator_Phase2/TransitionTable.h"
#include "Simulator_Phase2/PredictiveParser.h"
#include "ParsingRules/RulesParser.h"
#include "GeneratingNFA/Converter.h"
#include "MinimizedDFA/NFAtoDFA.h"
#include "MinimizedDFA/Minimization.h"
#include "CFG/GrammarParser.h"
#include "ll1/leftRecRem.h"
#include "ll1/leftFac.h"


using namespace std;

int main() {


//    // ------------------------------------------------------- TEST 1 ---------------------------------------------------
//    // Geek for Geeks Example
//    CFG grammar1;
//    ProductionElement* S = grammar1.createStartingSymbol("S");
//    ProductionElement* A = grammar1.createNewNonTerminal("A");
//    ProductionElement* B = grammar1.createNewNonTerminal("B");
//    B->gotEpsilon = true;
//    ProductionElement* C = grammar1.createNewNonTerminal("C");
//    C->gotEpsilon = true;
//    ProductionElement* a = grammar1.createNewTerminal("a");
//    ProductionElement* b = grammar1.createNewTerminal("b");
//    ProductionElement* d = grammar1.createNewTerminal("d");
//    ProductionElement* g = grammar1.createNewTerminal("g");
//    ProductionElement* h = grammar1.createNewTerminal("h");
//    ProductionElement* epsilon1 = grammar1.createNewTerminal("~");
//
//    // S --> ACB
//    Production* production11 = new Production();
//    production11->appendNewProductionElement(A);
//    production11->appendNewProductionElement(C);
//    production11->appendNewProductionElement(B);
//    grammar1.assignProductionToNonTerminal(production11, S->getSymbolValue());
//
//    // S --> Cbb
//    Production* production12 = new Production();
//    production12->appendNewProductionElement(C);
//    production12->appendNewProductionElement(b);
//    production12->appendNewProductionElement(b);
//    grammar1.assignProductionToNonTerminal(production12, S->getSymbolValue());
//
//    // S --> Ba
//    Production* production13 = new Production();
//    production13->appendNewProductionElement(B);
//    production13->appendNewProductionElement(a);
//    grammar1.assignProductionToNonTerminal(production13, S->getSymbolValue());
//
//    // A--> da
//    Production* production14 = new Production();
//    production14->appendNewProductionElement(d);
//    production14->appendNewProductionElement(a);
//    grammar1.assignProductionToNonTerminal(production14, A->getSymbolValue());
//
//    // A --> BC
//    Production* production15 = new Production();
//    production15->appendNewProductionElement(B);
//    production15->appendNewProductionElement(C);
//    grammar1.assignProductionToNonTerminal(production15, A->getSymbolValue());
//
//    // B --> g
//    Production* production16 = new Production();
//    production16->appendNewProductionElement(g);
//    grammar1.assignProductionToNonTerminal(production16, B->getSymbolValue());
//
//    // B --> epsilon
//    Production* production17 = new Production();
//    production17->appendNewProductionElement(epsilon1);
//    grammar1.assignProductionToNonTerminal(production17, B->getSymbolValue());
//
//    // C --> h
//    Production* production18 = new Production();
//    production18->appendNewProductionElement(h);
//    grammar1.assignProductionToNonTerminal(production18, C->getSymbolValue());
//
//    // C --> epsilon
//    Production* production19 = new Production();
//    production19->appendNewProductionElement(epsilon1);
//    grammar1.assignProductionToNonTerminal(production19, C->getSymbolValue());
//
//
//    for (auto itr : grammar1.terminals) {
//        cout << itr->getSymbolValue() << " <===" << endl;
//    }
//
//
//    cout << endl;
//    cout << "---------------------------------------First Test --------------------------------------------" << endl;
//    grammar1.debug();
//    FirstAndFollowLogic firstAndFollowLogic1(&grammar1);
//
//
//    cout << endl;
//    cout << "---------------------------------------First Test --------------------------------------------" << endl;

    // ---------------------------------------------------------- TEST 2 ----------------------------------------------
//    // Ex1 sheet 5
//    CFG grammar2;
//    ProductionElement* bexpr = grammar2.createStartingSymbol("bexpr");
//    ProductionElement* bexpr1 = grammar2.createNewNonTerminal("bexpr1");
//    bexpr1->gotEpsilon = true;
//    ProductionElement* btem = grammar2.createNewNonTerminal("btem");
//    ProductionElement* btem1 = grammar2.createNewNonTerminal("btem1");
//    btem1->gotEpsilon = true;
//    ProductionElement* bfactor = grammar2.createNewNonTerminal("bfactor");
//    ProductionElement* not1 = grammar2.createNewTerminal("not");
//    ProductionElement* or1 = grammar2.createNewTerminal("or");
//    ProductionElement* and1 = grammar2.createNewTerminal("and");
//    ProductionElement* true1 = grammar2.createNewTerminal("true");
//    ProductionElement* false1 = grammar2.createNewTerminal("false");
//    ProductionElement* quoteRightOpen = grammar2.createNewTerminal("(");
//    ProductionElement* quoteLeftOpen = grammar2.createNewTerminal(")");
//    ProductionElement* epsilon2 = grammar2.createNewTerminal("~");
//
//    // bexpr --> btem bexpr1
//    Production* production21 = new Production();
//    production21->appendNewProductionElement(btem);
//    production21->appendNewProductionElement(bexpr1);
//    grammar2.assignProductionToNonTerminal(production21, bexpr->getSymbolValue());
//
//    // bexpr1 --> or btem bexpr1
//    Production* production22 = new Production();
//    production22->appendNewProductionElement(or1);
//    production22->appendNewProductionElement(btem);
//    production22->appendNewProductionElement(bexpr1);
//    grammar2.assignProductionToNonTerminal(production22, bexpr1->getSymbolValue());
//
//    // bexpr1 --> epsilon
//    Production* production23 = new Production();
//    production23->appendNewProductionElement(epsilon2);
//    grammar2.assignProductionToNonTerminal(production23, bexpr1->getSymbolValue());
//
//    // btem --> bfactor btem1
//    Production* production24 = new Production();
//    production24->appendNewProductionElement(bfactor);
//    production24->appendNewProductionElement(btem1);
//    grammar2.assignProductionToNonTerminal(production24, btem->getSymbolValue());
//
//    // btem1 --> and bfactor btem1
//    Production* production25 = new Production();
//    production25->appendNewProductionElement(and1);
//    production25->appendNewProductionElement(bfactor);
//    production25->appendNewProductionElement(btem1);
//    grammar2.assignProductionToNonTerminal(production25, btem1->getSymbolValue());
//
//    // btem1 --> epsilon
//    Production* production26 = new Production();
//    production26->appendNewProductionElement(epsilon2);
//    grammar2.assignProductionToNonTerminal(production26, btem1->getSymbolValue());
//
//    // bfactor --> not bfactor
//    Production* production27 = new Production();
//    production27->appendNewProductionElement(not1);
//    production27->appendNewProductionElement(bfactor);
//    grammar2.assignProductionToNonTerminal(production27, bfactor->getSymbolValue());
//
//    // bfactor --> ( bexpr )
//    Production* production28 = new Production();
//    production28->appendNewProductionElement(quoteRightOpen);
//    production28->appendNewProductionElement(bexpr);
//    production28->appendNewProductionElement(quoteLeftOpen);
//    grammar2.assignProductionToNonTerminal(production28, bfactor->getSymbolValue());
//
//    // bfactor --> true
//    Production* production29 = new Production();
//    production29->appendNewProductionElement(true1);
//    grammar2.assignProductionToNonTerminal(production29, bfactor->getSymbolValue());
//
//    // bfactor --> false
//    Production* production210 = new Production();
//    production210->appendNewProductionElement(false1);
//    grammar2.assignProductionToNonTerminal(production210, bfactor->getSymbolValue());
//
//
//    cout << endl;
//    cout << "---------------------------------------Second Test --------------------------------------------" << endl;
//    grammar2.debug();
//    FirstAndFollowLogic firstAndFollowLogic2(&grammar2);
//    cout << endl;
//    cout << "---------------------------------------Second Test --------------------------------------------" << endl;


//    // ------------------------------------------- TEST 3 ---------------------------------------------
//    // Ex2 sheet 5
//    CFG grammar3;
//    ProductionElement* E = grammar3.createStartingSymbol("E");
//    ProductionElement* E1 = grammar3.createNewNonTerminal("E1");
//    E1->gotEpsilon = true;
//    ProductionElement* T = grammar3.createNewNonTerminal("T");
//    ProductionElement* T1 = grammar3.createNewNonTerminal("T1");
//    T1->gotEpsilon = true;
//    ProductionElement* F = grammar3.createNewNonTerminal("F");
//    ProductionElement* F1 = grammar3.createNewNonTerminal("F1");
//    F1->gotEpsilon = true;
//    ProductionElement* P = grammar3.createNewNonTerminal("P");
//
//    ProductionElement* a1 = grammar3.createNewTerminal("a");
//    ProductionElement* b1 = grammar3.createNewTerminal("b");
//    ProductionElement* plus = grammar3.createNewTerminal("+");
//    ProductionElement* mul = grammar3.createNewTerminal("*");
//    ProductionElement* Em = grammar3.createNewTerminal("Em");
//    ProductionElement* epsilon3 = grammar3.createNewTerminal("~");
//    ProductionElement* quoteRightOpen2 = grammar3.createNewTerminal("(");
//    ProductionElement* quoteLeftOpen2 = grammar3.createNewTerminal(")");
//
//    // E --> T E1
//    Production* production31 = new Production();
//    production31->appendNewProductionElement(T);
//    production31->appendNewProductionElement(E1);
//    grammar3.assignProductionToNonTerminal(production31, E->getSymbolValue());
//
//    // E1 --> + E
//    Production* production32 = new Production();
//    production32->appendNewProductionElement(plus);
//    production32->appendNewProductionElement(E);
//    grammar3.assignProductionToNonTerminal(production32, E1->getSymbolValue());
//
//    // E1 --> epsilon
//    Production* production33 = new Production();
//    production33->appendNewProductionElement(epsilon3);
//    grammar3.assignProductionToNonTerminal(production33, E1->getSymbolValue());
//
//    // T --> F T1
//    Production* production34 = new Production();
//    production34->appendNewProductionElement(F);
//    production34->appendNewProductionElement(T1);
//    grammar3.assignProductionToNonTerminal(production34, T->getSymbolValue());
//
//    // T1 --> T
//    Production* production35 = new Production();
//    production35->appendNewProductionElement(T);
//    grammar3.assignProductionToNonTerminal(production35, T1->getSymbolValue());
//
//    // T1 --> epsilon
//    Production* production36 = new Production();
//    production36->appendNewProductionElement(epsilon3);
//    grammar3.assignProductionToNonTerminal(production36, T1->getSymbolValue());
//
//    // F --> P F1
//    Production* production37 = new Production();
//    production37->appendNewProductionElement(P);
//    production37->appendNewProductionElement(F1);
//    grammar3.assignProductionToNonTerminal(production37, F->getSymbolValue());
//
//    // F1 --> * F
//    Production* production38 = new Production();
//    production38->appendNewProductionElement(mul);
//    production38->appendNewProductionElement(F);
//    grammar3.assignProductionToNonTerminal(production38, F1->getSymbolValue());
//
//    // F1 --> epsilon
//    Production* production39 = new Production();
//    production39->appendNewProductionElement(epsilon3);
//    grammar3.assignProductionToNonTerminal(production39, F1->getSymbolValue());
//
//    // P --> ( E )
//    Production* production310 = new Production();
//    production310->appendNewProductionElement(quoteRightOpen2);
//    production310->appendNewProductionElement(E);
//    production310->appendNewProductionElement(quoteLeftOpen2);
//    grammar3.assignProductionToNonTerminal(production310, P->getSymbolValue());
//
//    // P --> a
//    Production* production311 = new Production();
//    production311->appendNewProductionElement(a1);
//    grammar3.assignProductionToNonTerminal(production311, P->getSymbolValue());
//
//    // P --> b
//    Production* production312 = new Production();
//    production312->appendNewProductionElement(b1);
//    grammar3.assignProductionToNonTerminal(production312, P->getSymbolValue());
//
//    // P --> Em
//    Production* production313 = new Production();
//    production313->appendNewProductionElement(Em);
//    grammar3.assignProductionToNonTerminal(production313, P->getSymbolValue());
//
//
//    cout << endl;
//    cout << "---------------------------------------Third Test --------------------------------------------" << endl;
//    grammar3.debug();
//    FirstAndFollowLogic firstAndFollowLogic3(&grammar3);
//    cout << endl;
//    cout << "---------------------------------------Third Test --------------------------------------------" << endl;
//
//    // ------------------------------------------- TEST 4 ---------------------------------------------
//

    // ------------------------------------------- TEST 4 ---------------------------------------------

//
//    CFG grammar4;
//    ProductionElement* E11 = grammar4.createStartingSymbol("E");
//    ProductionElement* E111 = grammar4.createNewNonTerminal("E1");
//    E111->gotEpsilon = true;
//    ProductionElement* T11 = grammar4.createNewNonTerminal("T");
//    ProductionElement* T111 = grammar4.createNewNonTerminal("T1");
//    T111->gotEpsilon = true;
//    ProductionElement* F11 = grammar4.createNewNonTerminal("F");
//    ProductionElement* plus1 = grammar4.createNewTerminal("addop");
//    ProductionElement* mul1 = grammar4.createNewTerminal("mulop");
//    ProductionElement* quoteRightOpen11 = grammar4.createNewTerminal("(");
//    ProductionElement* quoteLeftOpen11 = grammar4.createNewTerminal(")");
//    ProductionElement* id = grammar4.createNewTerminal("id");
//    ProductionElement* epsilon11 = grammar4.createNewTerminal("\\L");
//
//    // E11 --> T11 E111
//    Production* production41 = new Production();
//    production41->appendNewProductionElement(T11);
//    production41->appendNewProductionElement(E111);
//    grammar4.assignProductionToNonTerminal(production41, E11->getSymbolValue());
//
//    // E111 --> + T11 E111
//    Production* production42 = new Production();
//    production42->appendNewProductionElement(plus1);
//    production42->appendNewProductionElement(T11);
//    production42->appendNewProductionElement(E111);
//    grammar4.assignProductionToNonTerminal(production42, E111->getSymbolValue());
//
//    // E111 --> epsilon11
//    Production* production43 = new Production();
//    production43->appendNewProductionElement(epsilon11);
//    grammar4.assignProductionToNonTerminal(production43, E111->getSymbolValue());
//
//    // T11 --> F11 T111
//    Production* production44 = new Production();
//    production44->appendNewProductionElement(F11);
//    production44->appendNewProductionElement(T111);
//    grammar4.assignProductionToNonTerminal(production44, T11->getSymbolValue());
//
//    // T111 --> * F11 T111
//    Production* production45 = new Production();
//    production45->appendNewProductionElement(mul1);
//    production45->appendNewProductionElement(F11);
//    production45->appendNewProductionElement(T111);
//    grammar4.assignProductionToNonTerminal(production45, T111->getSymbolValue());
//
//    // T111 --> epsilon11
//    Production* production46 = new Production();
//    production46->appendNewProductionElement(epsilon11);
//    grammar4.assignProductionToNonTerminal(production46, T111->getSymbolValue());
//
//    // F11 --> ( E11 )
//    Production* production47 = new Production();
//    production47->appendNewProductionElement(quoteRightOpen11);
//    production47->appendNewProductionElement(E11);
//    production47->appendNewProductionElement(quoteLeftOpen11);
//    grammar4.assignProductionToNonTerminal(production47, F11->getSymbolValue());
//
//    // F11 --> id
//    Production* production48 = new Production();
//    production48->appendNewProductionElement(id);
//    grammar4.assignProductionToNonTerminal(production48, F11->getSymbolValue());
//
//    cout << endl;
//    cout << "---------------------------------------Fourth Test --------------------------------------------" << endl;
//    grammar4.debug();


    cout << endl;
    cout << "---------------------------------------Fourth Test --------------------------------------------" << endl;

    GrammarParser x("grammarInput.txt");
    CFG grammar4 = x.getGrammar();
//    leftRecursionRemover* lrr = new  leftRecursionRemover(&grammar4);
//    lrr->preformLRR(true);
//    leftFac * lf = new leftFac(&grammar4,lrr->getHelper());
//    lf->preformLF(true);

    FirstAndFollowLogic firstAndFollowLogic4(&grammar4);


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
    cout << v.size();
    cout << "sajed";

    Simulator* simulator = new Simulator(v);
    simulator->resetInputFile("testInput.txt");
    string nextToken = "";
//    simulator->generateTokensFileAndSymbolTable();



    vector<ProductionElement*> terminals = grammar4.terminals;
    vector<ProductionElement*> nonTerminals = grammar4.nonTerminals;
    ProductionElement* startingProductionElement = grammar4.startingProductionElement;
    cout << endl << "\t";
    for (int i = 0; i < terminals.size(); i++) {
        cout << terminals[i]->getSymbolValue() << "  ";
    }
    cout << endl;
    for (int i = 0; i < nonTerminals.size(); i++) {
        cout << nonTerminals[i]->getSymbolValue() << endl;
    }
    cout << "Starting sym: " << startingProductionElement->getSymbolValue() << endl << endl;

    cout << "First sets" << endl;
    for (int i = 0; i < nonTerminals.size(); i++) {
        cout << nonTerminals[i]->getSymbolValue() << ":" ;
        cout << firstAndFollowLogic4.firstSets[nonTerminals[i]->getSymbolValue()]->name << ": ";
        Set * tempSet = firstAndFollowLogic4.firstSets[nonTerminals[i]->getSymbolValue()];
        for (auto j: firstAndFollowLogic4.firstSets[nonTerminals[i]->getSymbolValue()]->SetTerminals) {
            cout << "\t\t" << (j.first) << ":" << (j.second)->getSymbolValue() << "\t\t";
            tempSet->SetTerminalsProductions[j.first]->debugProduction();
        }

        cout << endl;
    }

    cout << "Follow sets" << endl;
    for (int i = 0; i < nonTerminals.size(); i++) {
        cout << nonTerminals[i]->getSymbolValue() << ":" ;
        cout << firstAndFollowLogic4.followSets[nonTerminals[i]->getSymbolValue()]->name << ": ";
        Set * tempSet = firstAndFollowLogic4.followSets[nonTerminals[i]->getSymbolValue()];
        for (auto j: tempSet->SetTerminals) {
            cout << "\t\t" << (j.first) << ":" << (j.second)->getSymbolValue();
            for (auto k: tempSet->SetNonTerminalsProductions) {
                cout << "hna";
                cout << k.first;
            }

        }
        cout << endl;
    }

    TransitionTable * transitionTable = new TransitionTable(terminals, nonTerminals, firstAndFollowLogic4.firstSets, firstAndFollowLogic4.followSets);
    transitionTable->printTransitionTable();
    PredictiveParser * pp = new PredictiveParser(startingProductionElement, transitionTable);
    pp->generateLeftMostDerivation(simulator);

    cout << endl;
    cout << "---------------------------------------Fourth Test --------------------------------------------" << endl;

//    // ------------------------------------------- TEST 5 ---------------------------------------------
//
//
//    CFG grammar5;
//    ProductionElement* S5 = grammar5.createStartingSymbol("S");
//    ProductionElement* R = grammar5.createNewNonTerminal("R");
//    R->gotEpsilon = true;
//    ProductionElement* U = grammar5.createNewNonTerminal("U");
//    U->gotEpsilon = true;
//    ProductionElement* V = grammar5.createNewNonTerminal("V");
//    V->gotEpsilon = true;
//    ProductionElement* T5 = grammar5.createNewNonTerminal("T");
//    T5->gotEpsilon = true;
//    ProductionElement* s = grammar5.createNewTerminal("s");
//    ProductionElement* u = grammar5.createNewTerminal("u");
//    ProductionElement* v = grammar5.createNewTerminal("v");
//    ProductionElement* b5 = grammar5.createNewTerminal("b");
//    ProductionElement* t = grammar5.createNewTerminal("t");
//    ProductionElement* epsilon5 = grammar5.createNewTerminal("~");
//
//    // S5 --> R T5
//    Production* production51 = new Production();
//    production51->appendNewProductionElement(R);
//    production51->appendNewProductionElement(T5);
//    grammar5.assignProductionToNonTerminal(production51, S5->getSymbolValue());
//
//    // R --> s U R b5
//    Production* production52 = new Production();
//    production52->appendNewProductionElement(s);
//    production52->appendNewProductionElement(U);
//    production52->appendNewProductionElement(R);
//    production52->appendNewProductionElement(b5);
//    grammar5.assignProductionToNonTerminal(production52, R->getSymbolValue());
//
//    // R --> epsilon5
//    Production* production53 = new Production();
//    production53->appendNewProductionElement(epsilon5);
//    grammar5.assignProductionToNonTerminal(production53, R->getSymbolValue());
//
//    // U --> u U
//    Production* production54 = new Production();
//    production54->appendNewProductionElement(u);
//    production54->appendNewProductionElement(U);
//    grammar5.assignProductionToNonTerminal(production54, U->getSymbolValue());
//
//    // U --> epsilon5
//    Production* production55 = new Production();
//    production55->appendNewProductionElement(epsilon5);
//    grammar5.assignProductionToNonTerminal(production55, U->getSymbolValue());
//
//    // V --> v V
//    Production* production56 = new Production();
//    production56->appendNewProductionElement(v);
//    production56->appendNewProductionElement(V);
//    grammar5.assignProductionToNonTerminal(production56, V->getSymbolValue());
//
//    // V --> epsilon
//    Production* production57 = new Production();
//    production57->appendNewProductionElement(epsilon5);
//    grammar5.assignProductionToNonTerminal(production57, V->getSymbolValue());
//
//    // T5 --> V t T5
//    Production* production58 = new Production();
//    production58->appendNewProductionElement(V);
//    production58->appendNewProductionElement(t);
//    production58->appendNewProductionElement(T5);
//    grammar5.assignProductionToNonTerminal(production58, T5->getSymbolValue());
//
//    // T5 --> epsilon
//    Production* production59 = new Production();
//    production59->appendNewProductionElement(epsilon5);
//    grammar5.assignProductionToNonTerminal(production59, T5->getSymbolValue());
//
//    cout << endl;
//    cout << "---------------------------------------Fifth Test --------------------------------------------" << endl;
//    grammar5.debug();
//    FirstAndFollowLogic firstAndFollowLogic5(&grammar5);
//    cout << endl;
//    cout << "---------------------------------------Fifth Test --------------------------------------------" << endl;


    return 0;
}
