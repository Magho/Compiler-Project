//
// Created by sajed on 20/04/19.
//

#include "PredictiveParser.h"

PredictiveParser::PredictiveParser(ProductionElement* start, TransitionTable* tb) {
    this->stk.push_back(new ProductionElement(true, "$"));
    this->stk.push_back(start);
    this->transitionTable = tb;
}
// TODO 5li al input text (id+(*id)$ ==> (idaddop(*id)$
// TODO ambiguity
// TODO undefiened token

void PredictiveParser::generateLeftMostDerivation(Simulator * simulator) {
    string nextToken = "";
    simulator->getNextToken(nextToken);
    cout << endl;
    while (this->stk.size() > 1 ) {

        printf("%2d: ", this->stk.size());
        string tempStr = "";
        for (int i = this->stk.size() - 1; i >= 0 ;--i)
            tempStr += this->stk[i]->symbolValue + " ";
        printf("%30s", tempStr.c_str());
        cout << "\t\t";
        printf("%20s", nextToken.c_str());
        cout << "\t\t\t\t\t\t\t\t";

        ProductionElement* pe = this->stk[this->stk.size() - 1];

        if (pe->isTerminal()) {
            if (pe->symbolValue.compare(nextToken) == 0) {
                this->stk.pop_back();
                cout << "match('" << nextToken << "')" << endl;

                simulator->getNextToken(nextToken);

            } else {
                cout << "[ERROR] Missing token: " << pe->symbolValue << endl;
                this->stk.pop_back();
            }

        } else { // Non terminal
            int row = this->transitionTable->getRowIndex(pe);
            int column = this->transitionTable->getColumnIndex(new ProductionElement(true, nextToken));
            if (row == -1|| column == -1) {
                cout << "\n\n [ERROR] Unrecognized token";
                break;
            }
            Production* production = this->transitionTable->transitionTable[row][column];
            if (production != nullptr) {
                if (production->isEpsilon) {
                    vector<ProductionElement*> productionValue = production->productionValue;
                    //print
                    cout << transitionTable->getLeftHandSide(row) << "  ==> ";
                    for ( int i = 0; i <  productionValue.size(); i++ ) {
                        cout << productionValue[i]->symbolValue;
                    }
                    cout << endl;
                    // end print
                    this->stk.pop_back();
                } else if (production->isSync) {
                    vector<ProductionElement*> productionValue = production->productionValue;
                    //print
                    cout << "[ERROR] Extra tokens starting with '" << nextToken << "'\n";
                    // end print
                    // end print
                    this->stk.pop_back();
                } else {
                    vector<ProductionElement*> productionValue = production->productionValue;
                    //print
                    cout << transitionTable->getLeftHandSide(row) << "  ==> ";
                    for ( int i = 0; i <  productionValue.size(); i++ ) {
                        cout << productionValue[i]->symbolValue;
                    }
                    cout << endl;
                    // end print
                    this->stk.pop_back();
                    for ( int i = productionValue.size() - 1; i >= 0; i-- ) {
                        this->stk.push_back(new ProductionElement (productionValue[i]->isTerminal(),
                                                                   productionValue[i]->symbolValue));
                    }
                }

            } else {
                cout << "[ERROR] Extra tokens starting with '" << nextToken << "'\n";
                simulator->getNextToken(nextToken);
                if (nextToken.compare("$") == 0) {
                    break;
                }
                bool unrecognized = false;
                while(!simulator->eof) {
                    int column = this->transitionTable->getColumnIndex(new ProductionElement(true, nextToken));
                    if (column == -1) {
                        cout << "\n\n [ERROR] Unrecognized token";
                        unrecognized = true;
                        break;
                    } else if (nextToken.compare("$") == 0) {
                        unrecognized = true;
                        break;
                    }
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
                if (unrecognized) {
                    break;
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

