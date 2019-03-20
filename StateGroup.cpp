#include <iostream>
#include <vector>
#include "Node.h"
using namespace std;


class StateGroup{
private:
        Node *potentialNode;

public :
    vector<Node *>* states;
    int number =-1;
    StateGroup(int Num){
        states = new vector<Node*>();
        number = Num;
        potentialNode = new Node(Num,false,false,INT_MAX,"");
    }

    Node* getGroupNode(){
        int highest_priority = INT_MAX;
        for(Node *toAdd : *states){
            potentialNode->start =potentialNode->start|| toAdd->start;
            potentialNode->final =potentialNode->final||toAdd->final;
            if(toAdd->priority< highest_priority){
                    highest_priority = toAdd->priority;
                    potentialNode->priority = toAdd->priority;
                    potentialNode->tokenName = toAdd->tokenName;
            }
        }
        return potentialNode;
    }
    bool addState(Node * toAdd){
        for (Node *s : *states){

            if(s->nodeNumber== toAdd->nodeNumber){

                return false;
            }
        }

        states->push_back(toAdd);

        return true;
    }

    bool operator ==(StateGroup s2){
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

};
