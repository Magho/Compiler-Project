#include <iostream>
#include<vector>
#include<string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../NFA.h"

using testing::Eq;
namespace {
    class ClassDeclaration : public testing::Test{
    public:
        ClassDeclaration();
    };

    ClassDeclaration::ClassDeclaration() {
    }
}



TEST_F(ClassDeclaration, NextNodeTest){

    Node node  (0, true, false); // create start node
    Node node1 (1, false, false) ; // create intermediate node
    Node node2 (2, false, true); // create final node

    node.addTransition(&node1, 'a'); // send address of the node
    node1.addTransition(&node2, 'b');
    vector<Node> nodes = node.getNextNode('a');
    vector<Node> nodes1 = node1.getNextNode('b');

    ASSERT_EQ(nodes.size(), 1);
    ASSERT_EQ(nodes[0].getNodeNumber(), 1);
    ASSERT_EQ(nodes1.size(), 1);
    ASSERT_EQ(nodes1[0].getNodeNumber(), 2);
}

TEST_F(ClassDeclaration, NFAMainStructureTest){

    Node nodeStart1  (0, true, false); // create start node
    Node nodeStart2  (3, true, false); // create start node
    Node nodeEpsilonPass (4, false, false); // create intermediate node reached by epsilon pass
    Node node1 (1, false, false) ; // create intermediate node
    Node node2 (2, false, true); // create final node

    nodeStart1.addTransition(&node1, 'a'); // send address of the node
    node1.addTransition(&node2, 'b');
    nodeStart2.addTransition(&nodeEpsilonPass, '~');
    vector<Node*> graph;
    graph.push_back(&nodeStart1);
    graph.push_back(&node1);
    graph.push_back(&node2);

    vector<Node*> startNodes;
    startNodes.push_back(&nodeStart1);
    startNodes.push_back(&nodeStart2);

    vector<Node*> finalNodes;
    finalNodes.push_back(&node2);

    vector<Node*> nodeWithEpsilonTransition;
    nodeWithEpsilonTransition.push_back(&nodeStart2);

    NFA nfa (graph, startNodes, finalNodes, "id");
    ASSERT_EQ(nfa.getVertexCount(), 3);

    vector<Node*> returnedStartNodes = nfa.getStartNodes();
    ASSERT_EQ(returnedStartNodes.size(), 2);
    ASSERT_EQ(returnedStartNodes.front()->getNodeNumber(), 0);
    ASSERT_EQ(returnedStartNodes.back()->getNodeNumber(), 3);

    vector<Node*> returnedFinalNodes = nfa.getFinalNodes();
    ASSERT_EQ(returnedFinalNodes.size(), 1);
    ASSERT_EQ(returnedFinalNodes.front()->getNodeNumber(), 2);
    ASSERT_EQ(returnedFinalNodes.back()->getNodeNumber(), 2);

    vector<Node*> returnesdGraphNodes = nfa.getGraphNodes();
    ASSERT_EQ(returnesdGraphNodes.size(), 3);
    ASSERT_EQ(returnesdGraphNodes.front()->getNodeNumber(), 0);
    ASSERT_EQ(returnesdGraphNodes.back()->getNodeNumber(), 2);

    vector<Node*> returnedEpsilonClosure = nfa.epsilonClosure(nodeWithEpsilonTransition);
    ASSERT_EQ(returnedEpsilonClosure.size(), 2);
    ASSERT_EQ(returnedEpsilonClosure.front()->getNodeNumber(), 3);
    ASSERT_EQ(returnedEpsilonClosure.back()->getNodeNumber(), 4);
}

TEST_F(ClassDeclaration, NFAOperationsTest){

    Node nfa1StartNode(10, true, false);
    Node nfa1FinalNode(11, false, true);
    Node nfa2StartNode(12, true, false);
    Node nfa2FinalNode(13, false, true);

    nfa1StartNode.addTransition(&nfa1FinalNode, 'a'); // send address of the node
    nfa2StartNode.addTransition(&nfa2FinalNode, 'a'); // send address of the node


    vector<Node*> nfa1graph;
    nfa1graph.push_back(&nfa1StartNode);
    nfa1graph.push_back(&nfa1FinalNode);
    vector<Node*> nfa2graph;
    nfa2graph.push_back(&nfa2StartNode);
    nfa2graph.push_back(&nfa2FinalNode);

    vector<Node*> nfa1StartNodes;
    nfa1StartNodes.push_back(&nfa1StartNode);
    vector<Node*> nfa2StartNodes;
    nfa2StartNodes.push_back(&nfa2StartNode);

    vector<Node*> nfa1FinalNodes;
    nfa1FinalNodes.push_back(&nfa1FinalNode);
    vector<Node*> nfa2FinalNodes;
    nfa2FinalNodes.push_back(&nfa2FinalNode);

    NFA nfa1 (nfa1graph, nfa1StartNodes, nfa1FinalNodes, "id");
    NFA nfa2 (nfa2graph, nfa2StartNodes, nfa2FinalNodes, "id");

    NFA kleneeNfa = nfa1.klenee();

    vector<Node*> kleneeNfaStartNodes = kleneeNfa.getStartNodes();
    ASSERT_EQ(kleneeNfaStartNodes.size(), 1);
    ASSERT_EQ(kleneeNfaStartNodes.front()->getNodeNumber(), 0);
    ASSERT_EQ(kleneeNfaStartNodes.back()->getNodeNumber(), 0);

    vector<Node*> kleneeNfaFinalNodes = kleneeNfa.getFinalNodes();
    ASSERT_EQ(kleneeNfaFinalNodes.size(), 1);
    ASSERT_EQ(kleneeNfaFinalNodes.front()->getNodeNumber(), 1);
    ASSERT_EQ(kleneeNfaFinalNodes.back()->getNodeNumber(), 1);

    vector<Node*> kleneeNfaGraphNodes = kleneeNfa.getGraphNodes();
    ASSERT_EQ(kleneeNfaGraphNodes.size(), 4);
    ASSERT_EQ(kleneeNfaGraphNodes.front()->getNodeNumber(), 10);
    ASSERT_EQ(kleneeNfaGraphNodes.back()->getNodeNumber(), 1);

    vector<Node*> kleneeNfaEpsilonClosure = kleneeNfa.epsilonClosure(kleneeNfaStartNodes);
    ASSERT_EQ(kleneeNfaEpsilonClosure.size(), 3);
    ASSERT_EQ(kleneeNfaEpsilonClosure.front()->getNodeNumber(),0);
    ASSERT_EQ(kleneeNfaEpsilonClosure.back()->getNodeNumber(),1);

}
