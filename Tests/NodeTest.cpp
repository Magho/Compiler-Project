#include <iostream>
#include<vector>
#include<string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../CombinedNFA.h"

using testing::Eq;
namespace {

    class NodeTest : public testing::Test{
        public:
            Node* node0;
            Node* node1;
            Node* node2;
            Node* node3;
            Node* node4;
            Node* node5;
            NodeTest();
    };

    NodeTest::NodeTest() {

        this->node0 = new Node (0, true , false, 0, "id");
        this->node1 = new Node (1, false, false, 0, "id");
        this->node2 = new Node (2, false, true , 0, "id");
        this->node3 = new Node (3, false, true , 0, "id");
        this->node4 = new Node (4, false, false, 0, "id");
        this->node5 = new Node (5, false, true , 0, "id");
        node0->addTransition(node1, 'a');
        node0->addTransition(node2, 'a');
        node0->addTransition(node3, 'b');
        node1->addTransition(node4, 'c');
        node1->addTransition(node5, 'd');
    }
}

TEST_F(NodeTest, NodeGetPossibleTransitions){

    vector<Transition*> node0Transitions = node0->getPossibleTransitions();
    ASSERT_EQ(node0Transitions.size(), 3);
    ASSERT_EQ(node0Transitions[0]->toNode->getNodeNumber(), 1);
    ASSERT_EQ(node0Transitions[1]->toNode->getNodeNumber(), 2);
    ASSERT_EQ(node0Transitions[2]->toNode->getNodeNumber(), 3);

    vector<Transition*> node1Transitions = node1->getPossibleTransitions();
    ASSERT_EQ(node1Transitions.size(), 2);
    ASSERT_EQ(node1Transitions[0]->toNode->getNodeNumber(), 4);
    ASSERT_EQ(node1Transitions[1]->toNode->getNodeNumber(), 5);

}

TEST_F(NodeTest, NodeGetNextNodes){

    vector<Node*> node0NexNodesWithSymbol_a = node0->getNextNode('a');
    vector<Node*> node1NexNodesWithSymbol_c = node1->getNextNode('c');
    vector<Node*> node2NexNodesWithSymbol_a = node2->getNextNode('a');
    // multi next nodes
    ASSERT_EQ(node0NexNodesWithSymbol_a.size(), 2);
    ASSERT_EQ(node0NexNodesWithSymbol_a[0]->getNodeNumber(), 1);
    ASSERT_EQ(node0NexNodesWithSymbol_a[1]->getNodeNumber(), 2);
    // one next nodes
    ASSERT_EQ(node1NexNodesWithSymbol_c.size(), 1);
    ASSERT_EQ(node1NexNodesWithSymbol_c[0]->getNodeNumber(), 4);
    // no next nodes
    ASSERT_EQ(node2NexNodesWithSymbol_a.size(), 0);
}

TEST_F(NodeTest, NodeLexeme){
    ASSERT_EQ(node4->getLexeme(), "ac");
    ASSERT_EQ(node2->getLexeme(), "a");
}
