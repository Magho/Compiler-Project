#include<vector>
#include<string>
#include "Transition.h"

using namespace std;

class Node {
private:
    int Number;
    bool start;
    bool final;
    string lexeme = "";
    // vector of pointers to all transitions
    vector<Transition*> transitions;
public:
    Node (int Number, bool start, bool final);
    void addTransition (Node* node_to, char transitionSymbol);
    vector<Transition*> getPossibleTransitions ();// return vector of pointers
    vector<Node> getNextNode (char transSymbol);
    bool isStart();
    bool isFinal();
    string getlexeme();
    int getNodeNumber();
};
