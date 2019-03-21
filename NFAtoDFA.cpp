#include "NFAtoDFA.h"
using namespace std;


    bool NFAtoDFA::isIn(vector<Node*> * nodes,Node *n ){
        for(Node *i : *nodes){
            if(i->nodeNumber == n->nodeNumber)return true;
        }
        return false;
    }


    /*find closure takes a state and finds the closure of that state and overloaded with set of states as parameters*/
    vector<Node *>* NFAtoDFA::findClosure(vector<Node *>* states){

        vector<Node*> * closure = new vector<Node*>();
        vector<Node *> * clStk = new vector<Node*>();
        for(Node *n : *states){
            clStk->push_back(n);
            closure->push_back(n);
        }
        while(!clStk->empty()){
            vector<Transition *> temp = clStk->back()->transitions;
            clStk->pop_back();
            for(Transition *t : temp){
                if(t->transitionSymbol == EPSILON){
                    if(!isIn(closure,t->toNode)){
                        closure->push_back(t->toNode);
                        clStk->push_back(t->toNode);
                    }
                }
            }
        }
//        if(!closure->empty()) {
//            cout << "find closure resulted in states :" << endl;
//            for (Node *n : *closure)cout << n->nodeNumber << " ";
//            cout << endl;
//        }
        return  closure;
    }


    vector<Node*>* NFAtoDFA::findToStates(vector<Node*>* states,char symbol){



        vector<Node*> * sts = new vector<Node*>();
        for(Node *n : *states){
            for(Transition *t : n->transitions){
                if(t->transitionSymbol == symbol){
                    if(!isIn(sts,t->toNode)){
                        sts->push_back(t->toNode);
                    }
                }
            }
        }

//        if(!sts->empty()) {
//            cout << "find to under i/p"<<(int)symbol<<" resulted in states :" << endl;
//            for (Node *n : *sts)cout << n->nodeNumber << " ";
//            cout << endl;
//        }
        return sts;
    }

    NFAtoDFA::NFAtoDFA(Node * start){
        NFAStart = start;
    }


    void NFAtoDFA::operate(){
        cout<<"converting from nfa to dfa ..."<<endl;
        /*start node given as input to that module*/
        Node * start = NFAStart;

        /*put the start state closure in the filling stack */
        vector<StateGroup*> fillingStk;
        vector<Node *>* tempStates = new vector<Node*>();
        tempStates->push_back(start);
        tempStates = findClosure(tempStates);
        StateGroup  *st = new StateGroup(0);
        st->states = tempStates;
        groupesTable.push_back(st);
        fillingStk.push_back(st);
        cout<<"got the start epsilon closure and set to group 0"<<endl;

        /*constructing fai*/
        fai = new Node(0,false,false,INT_MAX,"");
        StateGroup * faiG = new StateGroup(1);
        faiG->addState(fai);
        for(int i=0;i<128;i++){
            Transition * t = new Transition(faiG->getGroupNode(),(char)i);
            faiG->getGroupNode()->transitions.push_back(t);
        }

        cout<<"constructed fai and set to group 1 (not pushed to filling stack)"<<endl;


        /*looping until the stack is empty*/
        int ctr=1;
        while(!fillingStk.empty()){
//            cout<<"\n\nNFAtoDFA loop >> grp num :"<<fillingStk.back()->number<<"with curr states :"<<endl;
            tempStates = fillingStk.back()->states;
            StateGroup * currGrp = fillingStk.back();
            fillingStk.pop_back();

//            for(Node *n : *tempStates){
//                cout<<n->nodeNumber;
//            }
//            cout<<endl;
            for(int i =0;i<128;i++){                       // for each symbol in ascii table
                vector<Node*>* closure = findClosure(findToStates(tempStates,(char)i));

                /*case 1 : no state in the group go to another under i/p symbol i*/

                if((*closure).size()==0){                   // the epsilon closure is empty
                   // cout<<"at i/p :"<<i<<" going to fai"<<endl;
                    Transition * t = new Transition(faiG->getGroupNode(),i);
                    currGrp->getGroupNode()->transitions.push_back(t);
                    continue;
                }
                ctr++;
                StateGroup *st = new StateGroup(ctr);      // creating a group of states
                st->states = closure;                      // adding the states to go at symbol i

                /*case 2 : the group o states goes to an existed group*/

                /*denote the existance of a group of states in the tabel*/
                bool exists=false;
                for(StateGroup* sg : groupesTable){        //making sure that this group doesn't exist in the table
                    if(*sg==*st){
                      //  cout<<"at i/p :"<<i<<" going to existing group num :"<<sg->number<<endl;
                        exists=true;
                        ctr--;
                        Transition * t = new Transition(sg->getGroupNode(),i);

                        currGrp->getGroupNode()->transitions.push_back(t);

                        break;
                    }
                }


                /*case 3 : creating new table group*/

                if(!exists){                                  // if it doesn't exist we push it else it will be neglected
                    Transition * t = new Transition(st->getGroupNode(),i);
                    //cout<<"at i/p :"<<i<<" going to new created grp group num :"<<st->number<<endl;

                    currGrp->getGroupNode()->transitions.push_back(t);
                    groupesTable.push_back(st);
                    fillingStk.push_back(st);
                }
            }

        }
        groupesTable.push_back(faiG);

    }





    vector<Node *> NFAtoDFA::getResult(){
        vector<Node*> *res = new vector<Node*>();
        for(int i=0;i<groupesTable.size();i++){
            res->push_back((groupesTable.at(i)->getGroupNode()));
        }

        for(Node *n : *res){
            cout<<(n->start ? "ST-":"---")<<(n->final ? "f-  ":"--  ")<< n->nodeNumber<<":::";
            for(int  i=0;i<128;i++){
                cout<<n->transitions.at(i)->toNode->nodeNumber<<"-";
            }
            cout<<endl;
        }

        return *res;
    }


