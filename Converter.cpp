#include "Converter.h"

CombinedNFA Converter::regularExpressionToNFA(vector<stack<char>> reExpressions) {
    vector<NFA*> NFAs;
    for (auto &reExpression : reExpressions) {
        while (!reExpression.empty()) {
            NFAs.push_back(reToNFA(reExpression));
        }
    }
    Node* start = new Node (0, true, false);
    for (auto &NFA : NFAs) {
        for (int j = 0; j < NFA->getStartNodes().size(); ++j) {
            start->addTransition(NFA->getStartNodes()[j], '~');
        }
    }
    return CombinedNFA(start, NFAs);
}

NFA* Converter::reToNFA(stack<char> reExpression) {

}
