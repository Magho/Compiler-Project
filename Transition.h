#include<vector>
#include<string>
#include "Node.cpp"

using namespace std;

class Transition {
    public :
        Node *toNode;
        char transitionSymbol;
};
