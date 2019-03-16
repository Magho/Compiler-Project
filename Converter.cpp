#include "Converter.h"

CombinedNFA Converter::regularExpressionToNFA(vector<stack<char>> reExpressions) {
    for (auto &reExpression : reExpressions) {
        while (!reExpression.empty()) {
            reToNFA(reExpression);
        }
    }
}

NFA* Converter::reToNFA(stack<char> reExpression) {

}
