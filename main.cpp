#include <iostream>
#include <fstream>
#include <sstream>
#include "Simulator/Simulator.h"

using namespace std;

int main() {

    vector<Node*> DFATable;

    Node* node0 = new Node(0,true,false,0, "");
    Node* node2 = new Node(2,false,false,0,"Id");
    Node* node3 = new Node(3,false,true,0,"do");
    Node* node7 = new Node(7,false,false,0,"");
    Node* node8 = new Node(8,false,false,0,"");
    Node* node9 = new Node(9,false,false,0,"");
    Node* node10 = new Node(10,false,true,0,"double");
//    Node* node12 = new Node(12,false,true,0,"Id");
    Node* nodeD = new Node(99,false,false,0,"");

    char alphabet[128];
    for (int i = 0; i < 128; ++i) {
        alphabet[i] = i;
    }

    //Initialize nodes
    for (int j = 0; j < 128; ++j) {
        node0->addTransition(nodeD,alphabet[j]);
        node2->addTransition(nodeD,alphabet[j]);
        node3->addTransition(nodeD,alphabet[j]);
        node7->addTransition(nodeD,alphabet[j]);
        node8->addTransition(nodeD,alphabet[j]);
        node9->addTransition(nodeD,alphabet[j]);
        node10->addTransition(nodeD,alphabet[j]);
//        node12->addTransition(nodeD,alphabet[j]);
        nodeD->addTransition(nodeD,alphabet[j]);
    }
    node0->editTransition(node2,'d');
    node0->editTransition(nodeD,';');
    node2->editTransition(node3,'o');
    node3->editTransition(node7,'u');
    node7->editTransition(node8,'b');
    node8->editTransition(node9,'l');
    node9->editTransition(node10,'e');

    DFATable.push_back(node0);
    DFATable.push_back(node2);
    DFATable.push_back(node3);
    DFATable.push_back(node7);
    DFATable.push_back(node8);
    DFATable.push_back(node9);
    DFATable.push_back(node10);
//    DFATable.push_back(node12);
    DFATable.push_back(nodeD);

    Simulator* simulator = new Simulator(DFATable);
    simulator->resetInputFile("/home/sajed/CLionProjects/Compilers_Phase1/testInput.txt");
    string nextToken = "";
    while (simulator->getNextToken(nextToken)) {
        cout << "call: ";
        cout << nextToken << endl;
    }
//    simulator->getNextToken(nextToken);
//    cout << nextToken << endl;
//    simulator->getNextToken(nextToken);
//    cout << nextToken << endl;
//    simulator->getNextToken(nextToken);
//    cout << nextToken << endl;
//    simulator->getNextToken(nextToken);
//    cout << nextToken << endl;
//    simulator->getNextToken(nextToken);
//    cout << nextToken << endl;
//    simulator->getNextToken(nextToken);
//    cout << nextToken << endl;
//    simulator->getNextToken(nextToken);
//    cout << nextToken << endl;
//    simulator->getNextToken(nextToken);
//    cout << nextToken << endl;
    return 0;
}