//
// Created by sajed on 15/03/19.
//

#include "Simulator.h"

Simulator::Simulator(vector<Node> DFATable) {
    this->DFATable = DFATable;
}

void Simulator::getNextToken() {

}

void Simulator::generateTokensFile() {
    std::ifstream is("/home/sajed/CLionProjects/Compilers_Phase1/testInput.txt");     // open file

    char c;
    while (is.get(c)) {         // loop getting single characters
        std::cout << c;
    }

    is.close();                // close file
}
