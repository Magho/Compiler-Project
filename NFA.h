#include<vector>
#include<string>
#include "Node.h"
#include "Transition.h"

using namespace std;

class NFA {
    public:
        vector<Node> graph;
        vector<Node> startNodes;
        vector<Node> endNodes;

        int getVertexCount();
        void insertNode (Node nodeFrom, Node nodeTo, char transitionSymbol);
        void insertStartNode (Node node);
        void insertFinalNode (Node node, string tokenName);
        vector<Node> getStartNodes ();
        vector<Node> getFinalNodes ();
        vector<Node> epsilonClosure(vector<Node> nodes);
        void printNFA ();
};
