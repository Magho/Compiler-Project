#include <utility>
#include<vector>
#include<string>
#include<stack>
#include "CombinedNFA.h"

class Converter {
private:
    NFA* reToNFA (stack<char> reExpression);
public:
    // it creates for each stack a NFA then combine them
    CombinedNFA regularExpressionToNFA (vector<stack<char>> reExpressions);
};
