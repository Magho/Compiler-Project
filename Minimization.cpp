#include "Minimization.h"

using namespace std;


void Minimization::splitUponValidState(){
    StateGroup * valid = new StateGroup(groupsCntr);groupsCntr++;
    StateGroup * invalid = new StateGroup(groupsCntr);groupsCntr++;

    for(Node *n : *nodes){
        if(n->final){
 //           cout<< "valid : "<<n->nodeNumber<<endl;
            valid->addState(n);
        }else{
  //          cout<< "invalid : "<<n->nodeNumber<<endl;
            invalid->addState(n);
        }
    }
    /*initializing them to keep track of fai to put it at the end as aa convention*/
    fai = nodes->back();
    faiG = invalid;
    groups->push_back(valid);
    groups->push_back(invalid);
}
bool Minimization::equalStates(Node *a , Node *b){
  //  cout<<"\ncomparing equality for all inputs btw "<<a->nodeNumber <<" and " <<b->nodeNumber<<endl;
    for(int i =0;i<128;i++){
        if(a->transitions.at(i)->toNode->nodeNumber != b->transitions.at(i)->toNode->nodeNumber){
            return false;
        }
    }
    return true;
}
bool Minimization::splitToGroups(){
    int grSize = groups->size();
    vector<StateGroup *> *newGroups= new  vector<StateGroup *>() ;
    while(!groups->empty()){ //for each group
        StateGroup * grp  = groups->back();
        groups->pop_back();
        while(!grp->states->empty()){ //for each node in it
            Node * currentNode =grp->states->back();
            //create group for first node
            StateGroup * st = new StateGroup(currentNode->nodeNumber);
            if(currentNode==fai){
                faiG = st;
            }
            newGroups->push_back(st);
            st->addState(currentNode);
            int size = currentNode->transitions.size();
            for(int index=0;index<size;index++){
                st->getGroupNode()->transitions.push_back(currentNode->transitions.at(index));
            }
            grp->states->pop_back();
            for(int j=0;j< grp->states->size();j++){ //for each other nodes
                //if state j = i  add it to group i and remove it from this and i--
                if(equalStates(currentNode,grp->states->at(j))){
                    st->addState(grp->states->at(j));
                    grp->states->at(j)->nodeNumber = st->number;
                    grp->states->erase(grp->states->begin()+j);
                    j--;
                }
            }
        }
    }
    groups = newGroups;
    if(newGroups->size()==grSize){
        return false;
    }
    return true;

}

vector<Node*> Minimization::parseGroupsToNodes(){
    vector<Node*> *res = new vector<Node*>();
    while(!groups->empty()){
        if(groups->back()!= faiG) {
            res->push_back((groups->back()->getGroupNode()));
        }
        groups->pop_back();
    }
    res->push_back(faiG->getGroupNode());
cout<<endl;
    for(Node *n : *res){
        cout<<(n->start ? "ST-":"---")<<(n->final ? "f-  ":"--  ")<< n->nodeNumber<<":::";
        for(int  i=0;i<128;i++){
            cout<<n->transitions.at(i)->toNode->nodeNumber<<"-";
        }
        cout<<endl;
    }

    return *res;
}

Minimization::Minimization(vector<Node*> *v){
   groups = new   vector<StateGroup *>();
   nodes = v;
}

vector<Node*> Minimization::getMinimizedTable(){
    splitUponValidState();

    while(splitToGroups());

    return parseGroupsToNodes();
}
