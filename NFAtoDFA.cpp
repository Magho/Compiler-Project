#include<iostream>
#include<vector>
#include "StateGroup.cpp"
using namespace std;
#define EPSILON '~'
int main (){

}
class  NFAtoDFA{
private :
    vector<Node> *NFAStates;
    vector<StateGroup *> groupesTable;
public :
    NFAtoDFA(vector<Node> *states){
        NFAStates = states;
    }
    ~NFAtoDFA(){
    }
    bool isIn(vector<Node> * nodes,Node *n ){
        for(Node i : *nodes){
            if(i.Number == n->Number)return true;
        }
        return false;
    }
    /*find closure takes a state and finds the closure of that state and overloaded with set of states as parameters*/
    vector<Node>* findClosure(vector<Node >* states){
        vector<Node> * closure = new vector<Node>();
        vector<Node> * clStk = new vector<Node>();
        for(Node n : *states){
            clStk->push_back(n);
        }
        while(!clStk->empty()){
           for(Transition t : clStk->back().transitions){
            if(t.transitionSymbol == EPSILON){
                if(!isIn(closure,t.toNode)){
                    closure->push_back(*t.toNode);
                    clStk->push_back(*t.toNode);
                }
               }
           }
        }

    return  closure;
    }

    vector<Node>* findToStates(vector<Node>* states,char symbol){
        vector<Node> * sts = new vector<Node>();
        for(Node n : *states){
           for(Transition t : n.transitions){
            if(t.transitionSymbol == symbol){
                if(!isIn(sts,t.toNode)){
                    sts->push_back(*t.toNode);
                }
               }
           }
        }
        return sts;
    }

    void operate(){

        /*finding start state to start making DFA from its closure*/
        Node * start;
        for(Node s : *NFAStates){
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

        /*constructing fai*/
        Node * fai = new Node(0,false,false,"");
        for(char i=0;i<256;i++){
            Transition * t = new Transition();
            t->toNode = fai;
            t->transitionSymbol = i;
            fai->transitions.push_back(*t);
        }
         /*looping until the stack is empty*/
        int ctr=0;
        while(!fillingStk.empty()){
            tempStates = fillingStk.back()->states;
            for(char i =0;i<256;i++){                         // for each symbol in ascii table
                vector<Node>* closure = findClosure(findToStates(tempStates,i));
                if((*closure).size()==0){
                    Transition * t = new Transition();
                    t->toNode = fai;
                    t->transitionSymbol = i;
                    fillingStk.back()->potentialNode->transitions.push_back(*t);
                    continue;
                }
                StateGroup *st = new StateGroup(ctr);      // creating a group of states
                            ctr++;
                st->states = closure;                        // adding the states to go at symbol i

                bool exists=false;
                for(StateGroup* sg : groupesTable){          //making sure that this group doesn't exist in the table
                    if(*sg==*st){
                        exists=true;
                        ctr--;
                        Transition * t = new Transition();
                        t->toNode = sg->potentialNode;
                        t->transitionSymbol = i;
                        fillingStk.back()->potentialNode->transitions.push_back(*t);
                        //put the damn info to the current node in fillingst.ba
                        break;
                    }
                }
                if(!exists){                                  // if it doesn't exist we push it else it will be neglected
                    Transition * t = new Transition();
                    t->toNode = st->potentialNode;
                    t->transitionSymbol = i;
                    fillingStk.back()->potentialNode->transitions.push_back(*t);
                    groupesTable.push_back(st);
                    fillingStk.push_back(st);
                }
            }
            fillingStk.pop_back();

        }
        //at this point the closures must be filled with all the 256 ascii inputs
        //next step
        //2- test that part by printing results
        //3- convert from groupes to nodes
        //4- do minmization on nodes


    }

};
