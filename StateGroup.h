#ifndef STATEGROUP_H
#define STATEGROUP_H
#include <iostream>
#include<bits/stdc++.h>
#include <vector>
#include "Node.h"

using namespace std;

class StateGroup{
private:
    Node *potentialNode;

public :
    vector<Node *>* states;
    int number =-1;
    StateGroup(int Num);
    Node* getGroupNode();
    bool addState(Node * toAdd);
    bool operator ==(StateGroup s2);

};
#endif

