#include <utility>
#include<vector>
#include<string>
#include <map>
#include "Node.h"

using namespace std;

class NFA {
private:
    string tokenName;
    vector<Node*> startNodes;
    vector<Node*> finalNodes;
    vector<Node*> graph;
    void printRecursive(Node* node, int depth,map<int, bool>* map1);

public:
    NFA (vector<Node*> graph, vector<Node*> startNodes, vector<Node*> finalNodes, string tokenName); //Tested
    vector<Node*> getStartNodes ();
    vector<Node*> getFinalNodes ();
    vector<Node*> getGraphNodes ();
    NFA* kleneeClosure(int priority, int* nodeNumber, string tokenName);                             //Tested
    NFA* positiveClosure(int* nodeNumber);                                                           //Tested
    NFA* concatenate (NFA nfa,int priority, int* nodeNumber, string tokenName);                      //Tested
    NFA* orOperator (NFA nfa,int priority, int* nodeNumber, string tokenName);                       //Tested
    string getTokenName ();
    int getVertexCount();
    NFA* CreateCopyOfNFA(int *nodeNumber);
    void printNFA ();
};
