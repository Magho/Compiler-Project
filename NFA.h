#include <utility>
#include<vector>
#include<string>
#include "Node.h"

using namespace std;

class NFA {
private:
    vector<Node*> startNodes;// vector of pointers to all startNodes
    vector<Node*> finalNodes;// vector of pointers to all finalNodes
    vector<Node*> graph;// vector of pointers to all Nodes in the NFA
    void printRecursive(Node* node);
    void epsilonClosureRecursive(Node* node, vector<Node*>* result);

public:
    NFA (vector<Node*> graph, vector<Node*> startNodes, vector<Node*> finalNodes);
    int getVertexCount();
    vector<Node*> getStartNodes ();
    vector<Node*> getFinalNodes ();
    vector<Node*> getGraphNodes ();
    vector<Node*> epsilonClosure(vector<Node*> nodes);
    void printNFA ();
};
