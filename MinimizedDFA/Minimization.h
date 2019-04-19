#include <iostream>
#include <vector>
#include "StateGroup.h"

using namespace std;

class Minimization{
private:
    int groupsCntr=0;
    /*fai and fai group are used to keep track of fai to put it at the end
     * of the vector as aa convention*/
    StateGroup * faiG;
    Node *fai;
    vector<Node*> * nodes;
    vector<StateGroup *> *groups;
    void splitUponValidState();
    bool equalStates(Node *a , Node *b);
    bool splitToGroups();

    vector<Node *> parseGroupsToNodes();
public :
    Minimization(vector<Node*> *v);
    vector<Node *> getMinimizedTable();


};


