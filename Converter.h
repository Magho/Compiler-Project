#include <utility>
#include<vector>
#include<string>
#include <unordered_map>
#include <stack>
#include "CombinedNFA.h"


#define ADDITION (char)200
#define MULTIPLICATION (char)201
#define OR (char)202
class Converter {
private:
    NFA* reToNFA (stack<char> reExpression, int priority, vector<string> labels);
    int nodeNumber = 0;
    void handleSpecialChar(char &ch);
public:
    // it creates for each stack a NFA then combine them
    CombinedNFA regularExpressionToNFA (unordered_map <string, stack<char>> reExpressions, vector<string> labels);
};
