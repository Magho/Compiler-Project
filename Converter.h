#include <utility>
#include<vector>
#include<string>
#include <map>
#include <stack>
#include "CombinedNFA.h"

class Converter {
private:
    NFA* reToNFA (stack<char> reExpression, int priority, vector<string> labels);
    int nodeNumber = 0;
public:
    // it creates for each stack a NFA then combine them
    CombinedNFA regularExpressionToNFA (map<string, stack<char>> reExpressions, vector<string> labels);
};
