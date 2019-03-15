#include<iostream>
#include<vector>
#include "StateGroup.cpp"
using namespace std;


class  NFAtoDFA{
private :
    vector<Node> NFAStates;
    vector<StateGroup *> groupesTable;
public :
    NFAtoDFA(vector<Node> states){
        NFAStates = states;
    }
    ~NFAtoDFA(){
    }

    /*find closure takes a state and finds the closure of that state and overloaded with set of states as parameters*/
    vector<Node>* findClosure(vector<Node >* states){
    return  new vector<Node>();
    }

    vector<Node>* findToStates(vector<Node>* states,char symbol){
        return  new vector<Node>();

    }

    void operate(){

        /*finding start state to start making DFA from its closure*/
        Node * start;
        for(Node s : NFAStates){
            if(s.start){
                start = &s;
                break;
            }
        }

        /*put the start state closure in the stack filling stk */
         vector<StateGroup*> fillingStk;
         vector<Node>* tempStates = new vector<Node>();
         tempStates->push_back(*start);
         tempStates = findClosure(tempStates);
         StateGroup  *st = new StateGroup(0);
        st->states = tempStates;
        groupesTable.push_back(st);
        fillingStk.push_back(st);



         /*looping until the stack is empty*/
        int ctr=0;
        while(!fillingStk.empty()){
            ctr++;
            tempStates = fillingStk.back()->states;
            for(char i =0;i<256;i++){                         // for each symbol in ascii table
                vector<Node>* closure = findClosure(findToStates(tempStates,i));

                StateGroup *st = new StateGroup(ctr);      // creating a group of states
                st->states = closure;                        // adding the states to go at symbol i
                bool exists=false;
                for(StateGroup* sg : groupesTable){          //making sure that this group doesn't exist in the table
                    if(*sg==*st){
                        exists=true;
                        fillingStk.back().
                        //put the damn info to the current node in fillingst.ba
                        break;
                    }
                }
                if(!exists){                                  // if it doesn't exist we push it else it will be neglected
                    groupesTable.push_back(st);
                    fillingStk.push_back(st);
                }
            }

        }

    }

};
