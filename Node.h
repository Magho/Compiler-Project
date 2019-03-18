#include<vector>
#include<string>
#include "Transition.h"

using namespace std;

class Node {
private:
    int nodeNumber;
    bool start;
    bool final;
    string lexeme = "";
    vector<Transition*> transitions;
    int priority;
    string tokenName = "";
public:
    Node (int Number, bool start, bool final, int priority, string tokenName);   //Tested
    void addTransition (Node* node_to, char transitionSymbol);                   //Tested
    vector<Transition*> getPossibleTransitions ();// return vector of pointers   //Tested
    vector<Node*> getNextNode (char transSymbol);                                //Tested
    bool isStart();
    bool isFinal();
    void setStart();
    void setFinal();
    void removeStart();
    void removeFinal();
    string getLexeme();                                                          //Tested
    int getPriority();
    int getNodeNumber();                                                         //Tested
    void setNodeNumber(int nodenumber);                                          //Tested
    string getTokenName();
};
