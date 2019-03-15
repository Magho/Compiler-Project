#include<vector>
#include<string>

using namespace std;

class Transition;

class Node {
    public:
        int Number;
        bool start;
        bool final;
        string tokenName;
        vector<Transition> transitions;
        Node (int Number, bool start, bool final, string tokenName);
        void addTransition (Node& node_to, char transitionSymbol);
        vector<Transition> getPossibleTransitions ();
        Node getNextNode (char transitionSymbol); // Move
        bool isStart(Node node);
        bool isFinal(Node node);
};
