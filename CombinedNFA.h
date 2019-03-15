#include<vector>
#include<string>
#include<stack>
#include "Transition.h"
#include "Node.h"
#include "NFA.h"

using namespace std;

class CombinedNFA {
    public:
        NFA result;
        NFA regularExpressionToNFA (vector<stack<char>> reExpressions);
        NFA klenee (NFA nfa1, NFA nfa2);
        NFA concatinate (NFA nfa1, NFA nfa2);
        NFA orOperator (NFA nfa1, NFA nfa2);
};
