#include "Converter.h"
#define EPSILON 163

CombinedNFA Converter::regularExpressionToNFA(map<string, stack<char>> reExpressions, vector<string> labels) {

    vector<NFA*> NFAs;
    int priority = 0;
    for (auto &label : labels) {
        NFAs.push_back(reToNFA(reExpressions[label], priority, labels));
    }

    // start Node has no priority so -1 and NULL tokenName
    Node* start = new Node (0, true, false, -1, "");
    for (auto &NFA : NFAs) {
        vector<Node*> NFAsStartNodes = NFA->getStartNodes();
        for (int j = 0; j < NFAsStartNodes.size(); ++j) {
            start->addTransition(NFA->getStartNodes()[j], char(EPSILON));
        }
    }

    return CombinedNFA(start, NFAs);
}

NFA* Converter::reToNFA(stack<char> reExpression, int priority, vector<string> labels) {

    stack<NFA*> NFAStack;
    char temp;

    while (!reExpression.empty()){

        temp = reExpression.top();
        reExpression.pop();

        if (temp == '|') {

            NFA* NFA1 = NFAStack.top();
            NFAStack.pop();
            NFA* NFA2 = NFAStack.top();
            NFAStack.pop();
            NFAStack.push(NFA2->orOperator(*NFA1, priority, &this->nodeNumber, labels[priority]));

        } else if (temp == '`') {

            NFA* NFA1 = NFAStack.top();
            NFAStack.pop();
            NFA* NFA2 = NFAStack.top();
            NFAStack.pop();
            NFAStack.push(NFA2->concatenate(*NFA1, priority, &this->nodeNumber, labels[priority]));

        } else if (temp == '*'){

            NFA* NFA1 = NFAStack.top();
            NFAStack.pop();
            NFAStack.push(NFA1->kleneeClosure(priority, &this->nodeNumber, labels[priority]));

        } else if (temp == '+') {

            NFA* NFA1 = NFAStack.top();
            NFAStack.pop();
            NFAStack.push(NFA1->positiveClosure(&this->nodeNumber));

        } else {

            Node* NFA1node = new Node (++this->nodeNumber, false, false, priority, labels[priority]);
            Node* NFA1StartNode = new Node (++this->nodeNumber, true, false, priority, labels[priority]);
            Node* NFA1FinalNode = new Node (++this->nodeNumber, false, true, priority, labels[priority]);
            NFA1StartNode->addTransition(NFA1node,temp);
            NFA1node->addTransition(NFA1FinalNode,char(EPSILON));
            vector<Node*> NFA1graph;
            NFA1graph.push_back(NFA1node);
            NFA1graph.push_back(NFA1StartNode);
            NFA1graph.push_back(NFA1FinalNode);
            vector<Node*> NFA1StartNodes;
            NFA1StartNodes.push_back(NFA1StartNode);
            vector<Node*> NFA1FinalNodes;
            NFA1FinalNodes.push_back(NFA1FinalNode);

            NFA* NFA1 = new NFA (NFA1graph, NFA1StartNodes, NFA1FinalNodes,labels[priority]);
            NFAStack.push(NFA1);
        }
    }
    return NFAStack.top();
}
