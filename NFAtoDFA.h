#include <iostream>
#include <vector>
#include "StateGroup.h"
#define EPSILON (char)163

using  namespace std;


class  NFAtoDFA{
private :
    Node * fai;
    Node * NFAStart;
    vector<StateGroup *> groupesTable;

    bool isIn(vector<Node*> * nodes,Node *n );

    /*find closure takes a state and finds the closure of that state and overloaded with set of states as parameters*/
    vector<Node *>* findClosure(vector<Node *>* states);
    vector<Node*>* findToStates(vector<Node*>* states,char symbol);
public :
    NFAtoDFA(Node * start);

    void operate();

    vector<Node *> getResult();
};
