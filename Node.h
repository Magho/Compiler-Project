#include<vector>
#include<string>
#include "Transition.h"

using namespace std;

class Node {
public:
    int nodeNumber =0;
    bool start;
    bool final;
    string lexeme = "";
    vector<Transition*> transitions;
    int priority;
    string tokenName = "";
public:
    Node (int Number, bool start, bool final, int priority, string tokenName);   //Tested
    void addTransition (Node* node_to, char transitionSymbol);                   //Tested
    vector<Transition*> getPossibleTransitions ();// return vector of pointers   //Tested
    vector<Node*> getNextNode (char transSymbol);                                //Tested
    bool isStart();
    bool isFinal();
    void setStart();
    void setFinal();
    void removeStart();
    void removeFinal();
    string getLexeme();                                                          //Tested
    int getPriority();
    int getNodeNumber();                                                         //Tested
    void setNodeNumber(int nodenumber);                                          //Tested
    string getTokenName();
};
/*#include<vector>
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
*/
