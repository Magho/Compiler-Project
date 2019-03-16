#include<vector>
#include<string>
#include "Transition.h"

using namespace std;

class Node {
private:
    int Number;
    bool start;
    bool final;
    string tokenName;
    // vector of pointers to all transitions
    vector<Transition*> transitions;
public:
    Node (int Number, bool start, bool final, string tokenName);
    void addTransition (Node* node_to, char transitionSymbol);
    vector<Transition*> getPossibleTransitions ();// return vector of pointers
    vector<Node> getNextNode (char transSymbol); // Move
    bool isStart();
    bool isFinal();
    string getTokenName();
    int getNodeNumber();
};
