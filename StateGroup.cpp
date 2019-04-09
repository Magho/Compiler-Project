#include "StateGroup.h"
using namespace std;


vector<Node *>* states;
int number =-1;
StateGroup::StateGroup(int Num){
    states = new vector<Node*>();
    number = Num;
    potentialNode = new Node(Num,false,false,INT_MAX,"");
}

Node* StateGroup::getGroupNode(){
    int highest_priority = 1000000;
    for(Node *toAdd : *states){
        potentialNode->start =potentialNode->start|| toAdd->start;
        potentialNode->final =potentialNode->final||toAdd->final;
        if(toAdd->priority< highest_priority && toAdd->final){
            highest_priority = toAdd->priority;
            potentialNode->lexeme = toAdd->lexeme;
            potentialNode->priority = toAdd->priority;
            potentialNode->tokenName = toAdd->tokenName;
        }
    }
    return potentialNode;
}
bool StateGroup::addState(Node * toAdd){
    for (Node *s : *states){

        if(s->nodeNumber== toAdd->nodeNumber){

            return false;
        }
    }

    states->push_back(toAdd);

    return true;
}

bool StateGroup::operator ==(StateGroup s2){
    int num = s2.states->size();
    for(Node *sElem : *states){
        int prevNum =num;
        for(Node *s2Elem : *s2.states){
            if(sElem->nodeNumber==s2Elem->nodeNumber){
                num--;
                break;
            }
        }
        if(prevNum==num) return false;
    }
    if(num==0){
        return true;
    }else if(num > 0){
        return false;
    }else{
        return false;
        //Error -- a potential repeated element in group
    }
}

