#include <iostream>
#include "StateGroup.cpp"
#include <vector>

using namespace std;

class Minimization{
private:
    int groupsCntr=0;
    vector<Node> * nodes;
    vector<StateGroup *> *groups;
    void splitUponValidState(){
        StateGroup * valid = new StateGroup(groupsCntr);groupsCntr++;
        StateGroup * invalid = new StateGroup(groupsCntr);groupsCntr++;
        for(Node n : *nodes){
            if(n.final){
                valid->addState(&n);
            }else{
                invalid->addState(&n);
            }
        }
        groups->push_back(valid);
        groups->push_back(invalid);
    }
    bool equalStates(Node *a , Node *b){
        for(char i =0;i<128;i++){
            if(a->transitions.at(i).toNode->Number != b->transitions.at(i).toNode->Number){
                return false;
            }
        }
        return true;
    }
    bool splitToGroups(){
        int ctr =0;
        int grSize = groups->size();
        vector<StateGroup *> *newGroups= new  vector<StateGroup *>() ;
        while(!groups->empty()){ //for each group
            StateGroup * grp  = groups->back();
            while(!grp->states->empty()){ //for each node in it
                //create group for first node
                StateGroup * st = new StateGroup(ctr);
                newGroups->push_back(st);
                ctr++;
                st->addState(&grp->states->back());
                Node * currentNode =&grp->states->back();
                grp->states->pop_back();
                for(int j=0;j< grp->states->size();j++){ //for each other nodes
                    //if state j = i  add it to group i and remove it from this and i--
                    if(equalStates(currentNode,&grp->states->at(j))){
                        st->addState(&grp->states->at(j));
                        grp->states->at(j).Number = st->number;
                        grp->states->erase(grp->states->begin()+j);
                        j--;
                    }
                }
            }
            groups->pop_back();
        }
        groups = newGroups;
        if(newGroups->size()==grSize){
            return false;
        }
        return true;

    }

    vector<Node> parseGroupsToNodes(){
        vector<Node> *res = new vector<Node>();
        while(!groups->empty()){
            res->push_back(*(groups->back()->getGroupNode()));
            groups->pop_back();
        }
        return *res;
    }
public :
    Minimization(vector<Node> *v){
        nodes = v;
    }
    vector<Node> getMinimizedTable(){
        splitUponValidState();
        while(splitToGroups());
        return parseGroupsToNodes();
    }


};

