#include <iostream>
#include <vector>
#include "Transition.h"
using namespace std;


class StateGroup{
private:
        Node *potentialNode;
        bool higherPriority(string s1,string s2){
            if(s2=="")return true;
        return false;
        }
public :
    vector<Node>* states;
    int number =-1;
    StateGroup(int Num){
        number = Num;
        potentialNode = new Node(Num,false,false,"");
    }

    Node* getGroupNode(){
        for(Node toAdd : *states){
            potentialNode->start =potentialNode->start|| toAdd.start;
            potentialNode->final =potentialNode->final||toAdd.final;
            if(higherPriority(toAdd.tokenName,potentialNode->tokenName))potentialNode->tokenName = toAdd.tokenName;
        }
        return potentialNode;
    }
    bool addState(Node * toAdd){
        for (Node s : *states){
            if(s.Number== toAdd->Number){
                return false;
            }
        }
        states->push_back(*toAdd);
        return true;
    }
    bool operator ==(StateGroup s2){
        int num = s2.states->size();
        for(Node sElem : *states){
            int prevNum =num;
            for(Node s2Elem : *s2.states){
                if(sElem.Number==s2Elem.Number){
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
