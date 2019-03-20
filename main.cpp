
#include <iostream>
#include<vector>
#include<string>
#include "NFAtoDFA.h"
#include "Minimization.h"


int main(){
    Node *a = new Node(0,true,false,213,"");
    Node *b = new Node(1,false,false,213,"");
    Node *c = new Node(2,false,false,213,"");
    Node *d = new Node(3,false,false,213,"");
    Node *e = new Node(4,false,false,213,"");
    Node *f = new Node(5,false,false,213,"");
    Node *g = new Node(6,false, true,0,"id");

    a->addTransition(b,EPSILON);
    a->addTransition(c,EPSILON);
    a->addTransition(e,EPSILON);
    b->addTransition(d,'0');
    b->addTransition(d,'1');
    b->addTransition(c,EPSILON);
    c->addTransition(d,'0');
    c->addTransition(e,EPSILON);
    d->addTransition(e,'0');
    d->addTransition(f,'1');
    d->addTransition(g,EPSILON);
    e->addTransition(e,'0');
    e->addTransition(b,EPSILON);
    f->addTransition(e,'1');
    f->addTransition(g,EPSILON);
    NFAtoDFA *cnvrt = new NFAtoDFA(a);
    cnvrt->operate();
    vector<Node *> res = cnvrt->getResult();
    Minimization *minimization = new Minimization(&res);
    vector<Node*> v = minimization->getMinimizedTable();




    return 0;
}
/*
 *
 * merging has deleted these from main.cpp in master as i made my file with the same name :)
 *
 #include <gtest/gtest.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    return 0;
}

//#include <iostream>
//#include<vector>
//#include<string>
//#include "Converter.h"
//#define EPSILON 163
//
//using namespace std;
//int main() {
//    stack<char> stack1;
//    stack1.push('+');
//    stack1.push('|');
//    stack1.push('b');
//    stack1.push('a');
//    string label = "id";
//    map<string, stack<char>> map1;
//    map1.insert(pair<string, stack<char>>(label,stack1));
//    vector<string> labels;
//    labels.emplace_back("id");
//    Converter converter;
//    printf("\n");
//    converter.regularExpressionToNFA(map1,labels).printCombinedNFA();
//    return 0;
*/