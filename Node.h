#include<vector>
#include<string>

using namespace std;

class Transition;

class Node {
    private:
        int Number;
        bool start;
        bool final;
        string tokenName;
        vector<Transition> transitions;
    public:
        Node (int Number, bool start, bool final, string tokenName);
        void addTransition (Node node_to, char transitionSymbol);
        vector<Transition> getPossibleTransitions ();
        Node getNextNode (char transitionSymbol); // Move
};
