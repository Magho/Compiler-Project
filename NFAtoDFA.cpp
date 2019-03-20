#include<iostream>
#include<vector>
#include "StateGroup.cpp"
using namespace std;
#define EPSILON (char)163



class  NFAtoDFA{
private :
    Node * fai;
    Node * NFAStart;
    vector<StateGroup *> groupesTable;

    bool isIn(vector<Node*> * nodes,Node *n ){
        for(Node *i : *nodes){
            if(i->Number == n->Number)return true;
        }
        return false;
    }


    /*find closure takes a state and finds the closure of that state and overloaded with set of states as parameters*/
    vector<Node *>* findClosure(vector<Node *>* states){
        cout<<"find closure called with states :"<<endl;
        for(Node *n : *states)cout<<n->Number<<" ";
        cout<<endl;
        vector<Node*> * closure = new vector<Node*>();
        vector<Node *> * clStk = new vector<Node*>();
        for(Node *n : *states){
            clStk->push_back(n);
        }
        while(!clStk->empty()){
           for(Transition t : clStk->back()->transitions){
            if(t.transitionSymbol == EPSILON){
                if(!isIn(closure,t.toNode)){
                    closure->push_back(t.toNode);
                    clStk->push_back(t.toNode);
                }
               }
           }
        }
        cout<<"find closure resulted in states :"<<endl;
        for(Node* n : *closure)cout<<n->Number<<" ";
        cout<<endl<<endl;
    return  closure;
    }


    vector<Node*>* findToStates(vector<Node*>* states,char symbol){
        cout<<"find to called with i/p :"<<symbol<< " and curr states :"<<endl;
        for(Node *n : *states)cout<<n->Number<<" ";
        cout<<endl<<endl;


        vector<Node*> * sts = new vector<Node*>();
        for(Node *n : *states){
           for(Transition t : n->transitions){
            if(t.transitionSymbol == symbol){
                if(!isIn(sts,t.toNode)){
                    sts->push_back(t.toNode);
                }
               }
           }
        }


        cout<<"find to resulted in states :"<<endl;
        for(Node *n : *sts)cout<<n->Number<<" ";
        cout<<endl<<endl;
        return sts;
    }

public :
    NFAtoDFA(Node * start){
        NFAStart = start;
    }
    ~NFAtoDFA(){

    }

    void operate(){
        cout<<"converting from nfa to dfa ..."<<endl;
        /*start node given as input to that module*/
        Node * start = NFAStart;
        cout<<"start node is "<<start->Number<<endl;

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
        fai = new Node(0,false,false,"");
        for(char i=0;i<256;i++){
            Transition * t = new Transition();
            t->toNode = fai;
            t->transitionSymbol = i;
            fai->transitions.push_back(*t);
        }
        StateGroup * faiG = new StateGroup(1);
        faiG->addState(fai);
        cout<<"constructed fai and set to group 1 (not pushed to filling stack)"<<endl;

         /*looping until the stack is empty*/
        int ctr=1;
        while(!fillingStk.empty()){
            cout<<"NFAtoDFA loop >> grp num :"<<fillingStk.back()->number<<endl;
            tempStates = fillingStk.back()->states;
            for(char i =0;i<128;i++){                       // for each symbol in ascii table
                vector<Node*>* closure = findClosure(findToStates(tempStates,i));

                /*case 1 : no state in the group go to another under i/p symbol i*/

                if((*closure).size()==0){                   // the epsilon closure is empty
                    cout<<"at i/p :"<<i<<" going to fai"<<endl;
                    Transition * t = new Transition();
                    t->toNode = fai;
                    t->transitionSymbol = i;
                    fillingStk.back()->getGroupNode()->transitions.push_back(*t);
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
                        cout<<"at i/p :"<<i<<" going to existing group num :"<<sg->number<<endl;
                        exists=true;
                        ctr--;
                        Transition * t = new Transition();
                        t->toNode = sg->getGroupNode();
                        t->transitionSymbol = i;
                        fillingStk.back()->getGroupNode()->transitions.push_back(*t);
                        //put the damn info to the current node in fillingst.ba
                        break;
                    }
                }


                /*case 3 : creating new table group*/

                if(!exists){                                  // if it doesn't exist we push it else it will be neglected
                    Transition * t = new Transition();
                    cout<<"at i/p :"<<i<<" going to new created grp group num :"<<st->number<<endl;
                    t->toNode = st->getGroupNode();
                    t->transitionSymbol = i;
                    fillingStk.back()->getGroupNode()->transitions.push_back(*t);
                    groupesTable.push_back(st);
                    fillingStk.push_back(st);
                }
            }
            fillingStk.pop_back();

        }

        groupesTable.push_back(faiG);

    }





    vector<Node *> getResult(){
        vector<Node*> *res = new vector<Node>();
        int i=0;
        while(!groupesTable.empty()){
            res->push_back((groupesTable.at(i)->getGroupNode()));
            i++;
        }
        res->push_back(fai);




        for(Node *n : *res){
            cout<<(n.start ? "ST-":"---")<<n->Number<<":::";
            for(char i=0;i<128;i++){
                cout<< "( "<<i<<","<<n->transitions.at(i).toNode->Number<<") -";
            }
            cout<<endl;
        }

        return *res;
    }

};
