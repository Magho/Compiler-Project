#include <utility>

#include "Set.h"

void Set::finishMyFirstSet(bool isFollow) {
    while (true){
        if (this->SetNonTerminals.empty()){
            break;
        }
        for (auto setNonTerminal = this->SetNonTerminals.cbegin(); setNonTerminal != this->SetNonTerminals.cend() ; ) {

            for (auto terminal : setNonTerminal->second->SetTerminals){
                // if exist before just rewrite it
                // add terminal
                this->SetTerminals.insert(pair<string ,ProductionElement*> (terminal.first, terminal.second));
                // add its production if finishing first set
                if (!isFollow) {
                    this->SetTerminalsProductions.insert(
                            pair<string ,Production*>(terminal.first,
                                    this->SetNonTerminalsProductions[setNonTerminal->first]));
                }
            }
            for (auto nonTerminal : setNonTerminal->second->SetNonTerminals){
                // if exist before just rewrite it
                if(nonTerminal.first != this->name) {
                    this->SetNonTerminals.insert(pair<string ,Set*> (nonTerminal.first, nonTerminal.second));
                    if (!isFollow) {
                        this->SetNonTerminalsProductions.insert(
                                pair<string ,Production*>(nonTerminal.first,
                                                          this->SetNonTerminalsProductions[setNonTerminal->first]));
                    }
                }
            }
            // erase the first set we has just checked
            this->SetNonTerminals.erase(setNonTerminal++);
        }
    }
    //remove epsilon added to follow set
    if (isFollow){
        for (auto terminal = this->SetTerminals.cbegin(); terminal != this->SetTerminals.cend() ; ) {
            if(terminal->first == "~"){
                this->SetTerminals.erase(terminal++);
            }
        }
    }
}

void Set::printSetTerminals() {
    for(auto terminal : SetTerminals){
        cout << terminal.first << ", ";
    }
}
void Set::printSetNonTerminals() {
    for(auto terminal : SetNonTerminals){
        cout << terminal.first << ", ";
    }
}

void Set::printSetTerminalsProductions() {
    for(auto terminal : SetTerminalsProductions){
        cout << terminal.first << " : ";
        terminal.second->debugProductionCFG();
    }
}
