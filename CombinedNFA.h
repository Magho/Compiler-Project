#include <utility>
#include<vector>
#include<string>
#include<stack>
#include "NFA.h"

using namespace std;

class CombinedNFA {
private:
    Node* startNode;
    vector<NFA*> NFAs;// vector of pointers to all finalNodes
   void printRecursive(Node* node, int depth, map<int, bool>* map1);
public:
    CombinedNFA(Node* startNode, vector<NFA*> NFAs) {
        this->startNode = startNode;
        this->NFAs = std::move(NFAs);
    }
    void printCombinedNFA();

};