//
// Created by sajed on 20/04/19.
//

#include "PredictiveParser.h"

PredictiveParser::PredictiveParser(ProductionElement* start, TransitionTable* tb) {
    this->stk.push(new ProductionElement(true, "$"));
    this->stk.push(start);
    this->transitionTable = tb;
}

void PredictiveParser::generateLeftMostDerivation(Simulator * simulator) {
    string nextToken = "";
    simulator->getNextToken(nextToken);
    while (this->stk.size() > 1 ) {

        ProductionElement* pe = this->stk.top();

        if (pe->isTerminal()) {
            if (pe->symbolValue.compare(nextToken) == 0) {
                this->stk.pop();
                simulator->getNextToken(nextToken);

            } else {
                cout << "[ERROR] Missing token: " << pe->symbolValue << endl;
                this->stk.pop();
            }

        } else { // Non terminal
            int row = this->transitionTable->getRowIndex(pe);
            int column = this->transitionTable->getColumnIndex(new ProductionElement(true, nextToken));
            Production* production = this->transitionTable->transitionTable[row][column];
            if (production != nullptr) {
                vector<ProductionElement*> productionValue = production->productionValue;
                //print
                cout << transitionTable->getLeftHandSide(row) << "  ==> ";
                cout << productionValue[0]->symbolValue;
                for ( int i = 1; i <  productionValue.size(); i++ ) {
                    cout << " | " << productionValue[i]->symbolValue;
                }
                cout << endl;
                // end print
                for ( int i = productionValue.size() - 1; i >= 0; i-- ) {
                    this->stk.push(new ProductionElement (productionValue[i]->isTerminal(),
                                                          productionValue[i]->symbolValue));
                }
            } else {
                cout << "[ERROR] Extra tokens tarting with: " << nextToken << endl;
                simulator->getNextToken(nextToken);

                while(!simulator->eof) {
                    int column = this->transitionTable->getColumnIndex(new ProductionElement(true, nextToken));
                    Production* production = this->transitionTable->transitionTable[row][column];
                    if (production == nullptr) {
                        simulator->getNextToken(nextToken);
                    } else if (production->isSync){
                        simulator->getNextToken(nextToken);
                        break;
                    } else {
                        break;
                    }
                }
            }

        }
    }
    if (this->stk.size() == 1 && simulator->eof) {
        cout << "[Info] Halt successfuly" << endl;
    } else if (this->stk.size() == 1 && !simulator->eof) {
        cout << "[Error] Stack is empty" << endl;
    }

}

void PredictiveParser::getIntoPanicMode() {
    cout << "Missing";
}

