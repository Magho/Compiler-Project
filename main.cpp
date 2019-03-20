#include <iostream>
#include<vector>
#include<string>
#include "NFAtoDFA.h"
#include "Minimization.h"
#define  EPSLOn (char)163
int main(){
    Node *a = new Node(0,true,false,213,"");
    Node *b = new Node(1,false,false,213,"");
    Node *c = new Node(2,false,false,213,"");
    Node *d = new Node(3,false,false,213,"");
    Node *e = new Node(4,false,false,213,"");
    Node *f = new Node(5,false,false,213,"");
    Node *g = new Node(6,false, true,0,"id");

    a->addTransition(b,EPSLOn);
    a->addTransition(c,EPSLOn);
    a->addTransition(e,EPSLOn);
    b->addTransition(d,'0');
    b->addTransition(d,'1');
    b->addTransition(c,EPSLOn);
    c->addTransition(d,'0');
    c->addTransition(e,EPSLOn);
    d->addTransition(e,'0');
    d->addTransition(f,'1');
    d->addTransition(g,EPSLOn);
    e->addTransition(e,'0');
    e->addTransition(b,EPSLOn);
    f->addTransition(e,'1');
    f->addTransition(g,EPSLOn);
    NFAtoDFA *cnvrt = new NFAtoDFA(a);
    cnvrt->operate();
    vector<Node *> res = cnvrt->getResult();
    Minimization *minimization = new Minimization(&res);
    vector<Node*> v = minimization->getMinimizedTable();




    return 0;
}