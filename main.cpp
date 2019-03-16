#include <iostream>
#include<vector>
#include<string>
#include "NFA.h"

using namespace std;
int main() {

    //*********************************************** Node testes ****************************************************//

    Node node  (0, true, false); // create start node
    Node nodeStart2  (3, true, false); // create start node
    Node nodeEpsilonPass (4, false, false); // create intermediate node reached by epsilon pass
    Node node1 (1, false, false) ; // create intermediate node
    Node node2 (2, false, true); // create final node

    node.addTransition(&node1, 'a'); // send address of the node
    node1.addTransition(&node2, 'b');
    nodeStart2.addTransition(&nodeEpsilonPass, '~');

    vector<Node> nodes = node.getNextNode('a');
//    cout << nodes.size() << endl; // expected output is 1
//    cout << nodes[0].getNodeNumber()<< endl; // expected output is 1

    vector<Node> nodes1 = node1.getNextNode('b');
//    cout << nodes1.size() << endl; // expected 1
//    cout << nodes1[0].getNodeNumber()<< endl; // expected 2

    // ************************************************ NFA tests ****************************************************//

    vector<Node*> graph;
    graph.push_back(&node);
    graph.push_back(&node1);
    graph.push_back(&node2);

    vector<Node*> startNodes;
    startNodes.push_back(&node);
    startNodes.push_back(&nodeStart2);

    vector<Node*> finalNodes;
    finalNodes.push_back(&node2);

    vector<Node*> nodeWithEpsilonTransition;
    nodeWithEpsilonTransition.push_back(&nodeStart2);

    NFA nfa (graph, startNodes, finalNodes, "id");
//    cout << nfa.getVertexCount() << endl; // expected 3

    vector<Node*> returnedStartNodes = nfa.getStartNodes();
//    cout << returnedStartNodes.size() << endl; // expected 1
//    cout << returnedStartNodes.front()->getNodeNumber() << endl; // expected 0
//    cout << returnedStartNodes.back()->getNodeNumber() << endl; // expected 0

    vector<Node*> returnedFinalNodes = nfa.getFinalNodes();
//    cout << returnedFinalNodes.size() << endl; // expected 1
//    cout << returnedFinalNodes.front()->getNodeNumber() << endl; // expected 2
//    cout << returnedFinalNodes.back()->getNodeNumber() << endl; // expected 2

    vector<Node*> returnesdGraphNodes = nfa.getGraphNodes();
//    cout << returnesdGraphNodes.size() << endl; // expected 3
//    cout << returnesdGraphNodes.front()->getNodeNumber() << endl; // expected 0
//    cout << returnesdGraphNodes.back()->getNodeNumber() << endl; // expected 2

    vector<Node*> returnedEpsilonClosure = nfa.epsilonClosure(nodeWithEpsilonTransition);
//    cout << returnedEpsilonClosure.size() << endl; // expected 2
//    cout << returnedEpsilonClosure.front()->getNodeNumber() << endl; // expected 3
//    cout << returnedEpsilonClosure.back()->getNodeNumber() << endl; // expected 4

//    nfa.printNFA();


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
//    cout << kleneeNfaStartNodes.size() << endl; // expected 1
//    cout << kleneeNfaStartNodes.front()->getNodeNumber() << endl; // expected 0
//    cout << kleneeNfaStartNodes.back()->getNodeNumber() << endl; // expected 0

    vector<Node*> kleneeNfaFinalNodes = kleneeNfa.getFinalNodes();
//    cout << kleneeNfaFinalNodes.size() << endl; // expected 1
//    cout << kleneeNfaFinalNodes.front()->getNodeNumber() << endl; // expected 1
//    cout << kleneeNfaFinalNodes.back()->getNodeNumber() << endl; // expected 1

    vector<Node*> kleneeNfaGraphNodes = kleneeNfa.getGraphNodes();
//    cout << kleneeNfaGraphNodes.size() << endl; // expected 4
//    cout << kleneeNfaGraphNodes.front()->getNodeNumber() << endl; // expected 10
//    cout << kleneeNfaGraphNodes.back()->getNodeNumber() << endl; // expected 1

    vector<Node*> kleneeNfaEpsilonClosure = kleneeNfa.epsilonClosure(kleneeNfaStartNodes);
//    cout << kleneeNfaEpsilonClosure.size() << endl; // expected 3
//    cout << kleneeNfaEpsilonClosure.front()->getNodeNumber() << endl; // expected 0
//    cout << kleneeNfaEpsilonClosure.back()->getNodeNumber() << endl; // expected 1

    return 0;
}