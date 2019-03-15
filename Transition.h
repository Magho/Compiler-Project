#include<vector>
#include<string>
#include "Node.cpp"

using namespace std;

class Transition {
    public :
        Transition(Node* n,char c){
            this.toNode = n;
            this.transitionSymbol =c;
        }
        Node *toNode;
        char transitionSymbol;
};
