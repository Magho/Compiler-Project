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
    vector<Transition> transitions;
public:
    Node (int Number, bool start, bool final, string tokenName);
    void addTransition (Node* node_to, char transitionSymbol);
    vector<Transition> getPossibleTransitions ();
    vector<Node> getNextNode (char transSymbol); // Move
    bool isStart();
    bool isFinal();
    string getTokenName();
    int getNodeNumber();
};
