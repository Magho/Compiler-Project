#include <iostream>
#include<vector>
#include<string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../CombinedNFA.h"
#define EPSILON 163

using testing::Eq;
namespace {

    class NFATest : public testing::Test{
        public:
            Node* node0;
            Node* node1;
            Node* node2;
            Node* node3;
            Node* node4;
            Node* node5;
            vector<Node*> nfa1graph;
            vector<Node*> nfa1startNodes;
            vector<Node*> nfa1finalNodes;
            NFA* nfa1;
            int nodeNumber = 0;

            Node* node6;
            Node* node7;
            vector<Node*> nfa2graph;
            vector<Node*> nfa2startNodes;
            vector<Node*> nfa2finalNodes;
            NFA* nfa2;

            NFATest();
    };

    NFATest::NFATest() {

        this->node0 = new Node (this->nodeNumber, true , false, 0, "id");
        this->node1 = new Node (++this->nodeNumber, false, false, 0, "id");
        this->node2 = new Node (++this->nodeNumber, false, true , 0, "id");
        this->node3 = new Node (++this->nodeNumber, false, true , 0, "id");
        this->node4 = new Node (++this->nodeNumber, false, true, 0, "id");
        this->node5 = new Node (++this->nodeNumber, false, true , 0, "id");
        node0->addTransition(node1, 'a');
        node0->addTransition(node2, 'a');
        node0->addTransition(node3, 'b');
        node1->addTransition(node4, 'c');
        node1->addTransition(node5, 'd');

        nfa1graph.push_back(node0);
        nfa1graph.push_back(node1);
        nfa1graph.push_back(node2);
        nfa1graph.push_back(node3);
        nfa1graph.push_back(node4);
        nfa1graph.push_back(node5);
        nfa1startNodes.push_back(node0);
        nfa1finalNodes.push_back(node2);
        nfa1finalNodes.push_back(node3);
        nfa1finalNodes.push_back(node4);
        nfa1finalNodes.push_back(node5);
        this->nfa1 = new NFA (nfa1graph, nfa1startNodes, nfa1finalNodes, "id");

        this->node6 = new Node (++this->nodeNumber, true , false, 1, "digit");
        this->node7 = new Node (++this->nodeNumber, false, true , 1, "digit");
        node6->addTransition(node7, char(EPSILON));

        nfa2graph.push_back(node6);
        nfa2graph.push_back(node7);
        nfa2startNodes.push_back(node6);
        nfa2finalNodes.push_back(node7);
        this->nfa2 = new NFA (nfa2graph, nfa2startNodes, nfa2finalNodes, "digit");
    }
}

TEST_F(NFATest, GetKleneeClouserNfa1Test){

    NFA* kleneeNfa = nfa2->kleneeClosure(1,&this->nodeNumber,"digit");
    vector<Node*> kleneeNfaStartNodes = kleneeNfa->getStartNodes();
    ASSERT_EQ(kleneeNfaStartNodes.size(), 1);
    ASSERT_EQ(kleneeNfaStartNodes[0]->getNodeNumber(), 8);

    vector<Node*> kleneeNfaFinalNodes = kleneeNfa->getFinalNodes();
    ASSERT_EQ(kleneeNfaFinalNodes.size(), 1);
    ASSERT_EQ(kleneeNfaFinalNodes[0]->getNodeNumber(), 9);

    vector<Node*> kleneeNfaGraphNodes = kleneeNfa->getGraphNodes();
    ASSERT_EQ(kleneeNfaGraphNodes.size(), 4);
    ASSERT_EQ(kleneeNfaGraphNodes.front()->getNodeNumber(), 6);
    ASSERT_EQ(kleneeNfaGraphNodes.back()->getNodeNumber(), 9);

    printf("\n");
    kleneeNfa->printNFA();
}

TEST_F(NFATest, GetPositiveClouserNfa1Test){

    NFA* positiveClosure = nfa2->positiveClosure(&this->nodeNumber);
    vector<Node*> positiveClosureNfaStartNodes = positiveClosure->getStartNodes();
    ASSERT_EQ(positiveClosureNfaStartNodes.size(), 1);
    ASSERT_EQ(positiveClosureNfaStartNodes[0]->getNodeNumber(), 12);

    vector<Node*> positiveClosureNfaFinalNodes = positiveClosure->getFinalNodes();
    ASSERT_EQ(positiveClosureNfaFinalNodes.size(), 1);
    ASSERT_EQ(positiveClosureNfaFinalNodes[0]->getNodeNumber(), 13);

    vector<Node*> positiveClosureNfaGraphNodes = positiveClosure->getGraphNodes();
    ASSERT_EQ(positiveClosureNfaGraphNodes.size(), 8);
    ASSERT_EQ(positiveClosureNfaGraphNodes.front()->getNodeNumber(), 8);
    ASSERT_EQ(positiveClosureNfaGraphNodes.back()->getNodeNumber(), 13);

    printf("\n");
    positiveClosure->printNFA();
}

TEST_F(NFATest, GetConcatNfa1AndNfa2Test){

    NFA* concateNfa = nfa2->concatenate(*nfa1, 1, &this->nodeNumber, "digit");
    vector<Node*> kleneeNfaStartNodes = concateNfa->getStartNodes();
    ASSERT_EQ(kleneeNfaStartNodes.size(), 1);
    ASSERT_EQ(kleneeNfaStartNodes[0]->getNodeNumber(), 8);

    vector<Node*> kleneeNfaFinalNodes = concateNfa->getFinalNodes();
    ASSERT_EQ(kleneeNfaFinalNodes.size(), 1);
    ASSERT_EQ(kleneeNfaFinalNodes[0]->getNodeNumber(), 9);

    vector<Node*> kleneeNfaGraphNodes = concateNfa->getGraphNodes();
    ASSERT_EQ(kleneeNfaGraphNodes.size(), 10);
    ASSERT_EQ(kleneeNfaGraphNodes.front()->getNodeNumber(), 6);
    ASSERT_EQ(kleneeNfaGraphNodes.back()->getNodeNumber(), 9);

    printf("\n");
    concateNfa->printNFA();
}

TEST_F(NFATest, GetOrNfa1AndNfa2Test){

    NFA* orNfa = nfa2->orOperator(*nfa1, 1, &this->nodeNumber, "digit");
    vector<Node*> orNfaStartNodes = orNfa->getStartNodes();
    ASSERT_EQ(orNfaStartNodes.size(), 1);
    ASSERT_EQ(orNfaStartNodes[0]->getNodeNumber(), 8);

    vector<Node*> orNfaFinalNodes = orNfa->getFinalNodes();
    ASSERT_EQ(orNfaFinalNodes.size(), 1);
    ASSERT_EQ(orNfaFinalNodes[0]->getNodeNumber(), 9);

    vector<Node*> orNfaGraphNodes = orNfa->getGraphNodes();
    ASSERT_EQ(orNfaGraphNodes.size(), 10);
    ASSERT_EQ(orNfaGraphNodes.front()->getNodeNumber(), 6);
    ASSERT_EQ(orNfaGraphNodes.back()->getNodeNumber(), 9);

    printf("\n");
    orNfa->printNFA();
}
