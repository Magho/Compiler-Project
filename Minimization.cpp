#include <iostream>
#include "StateGroup.cpp"
#include <vector>

using namespace std;

class Minimization{
private:
    int groupsCntr=0;
    vector<Node> * nodes;
    vector<StateGroup *> groups;
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
        groups.push_back(valid);
        groups.push_back(invalid);
    }
    bool splitToGroups(){


    }
    void updateGroupsNums(){


    }
    vector<Node> parseGroupsToNodes(){


    }
public :
    Minimization(vector<Node> *v){
        nodes = v;
    }
    vector<Node> getMinimizedTable(){
        splitUponValidState();
        while(splitToGroups()){
            updateGroupsNums();
        }
        return parseGroupsToNodes();
    }


};


/*
Algorithm :
1- group the states to 2 groups final(valid) and others
2-
*/
