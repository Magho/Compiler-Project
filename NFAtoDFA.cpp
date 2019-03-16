#include<iostream>
#include<vector>
#include "StateGroup.cpp"
using namespace std;
#define EPSILON 163
int main (){

}
class  NFAtoDFA{
private :
    Node * fai;
    Node *NFAStart;
    vector<StateGroup *> groupesTable;
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

public :
    NFAtoDFA(Node * start){
        NFAStart = start;
    }
    ~NFAtoDFA(){

    }

    void operate(){

        /*finding start state to start making DFA from its closure*/
        Node * start = NFAStart;

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
        fai = new Node(0,false,false,"");
        for(char i=0;i<256;i++){
            Transition * t = new Transition();
            t->toNode = fai;
            t->transitionSymbol = i;
            fai->transitions.push_back(*t);
        }
        StateGroup * faiG = new StateGroup(0);
        faiG->addState(fai);
         /*looping until the stack is empty*/
        int ctr=0;
        while(!fillingStk.empty()){
            tempStates = fillingStk.back()->states;
            for(char i =0;i<128;i++){                         // for each symbol in ascii table
                vector<Node>* closure = findClosure(findToStates(tempStates,i));
                if((*closure).size()==0){
                    Transition * t = new Transition();
                    t->toNode = fai;
                    t->transitionSymbol = i;
                    fillingStk.back()->getGroupNode()->transitions.push_back(*t);
                    continue;
                }
                ctr++;
                StateGroup *st = new StateGroup(ctr);      // creating a group of states
                st->states = closure;                        // adding the states to go at symbol i

                bool exists=false;
                for(StateGroup* sg : groupesTable){          //making sure that this group doesn't exist in the table
                    if(*sg==*st){
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
                if(!exists){                                  // if it doesn't exist we push it else it will be neglected
                    Transition * t = new Transition();
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
        //at this point the closures must be filled with all the 256 ascii inputs
        //next step
        //2- test that part by printing results
        //3- convert from groupes to nodes And add the dummy to the end
        //4- do minmization on nodes

    }
    vector<Node> getResult(){
        vector<Node> *res = new vector<Node>();
        while(!groupesTable.empty()){
            res->push_back(*(groupesTable.back()->getGroupNode()));
            groupesTable.pop_back();
        }
        res->push_back(*fai);
        return *res;
    }

};
