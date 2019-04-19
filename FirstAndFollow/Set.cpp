#include "Set.h"

void Set::finishMyFirstSet(bool isFollow) {
    while (true){
        if (this->SetNonTerminals.empty()){
            break;
        }
        for(auto SetNonTerminal : SetNonTerminals){
            for (auto terminal : SetNonTerminal.second->SetTerminals){
                // if exist before just rewrite it
                this->SetTerminals.insert(pair<string ,ProductionElement*> (terminal.first, terminal.second));
            }
            for (auto terminal : SetNonTerminal.second->SetNonTerminals){
                // if exist before just rewrite it
                this->SetNonTerminals.insert(pair<string ,Set*> (terminal.first, terminal.second));
            }
            // erase the first set we has just checked
            this->SetNonTerminals.erase(SetNonTerminal.first);
        }
    }
    //remove epsilon added to follow set
    if (isFollow){
        for(auto termianl : this->SetTerminals){
            if(termianl.first == "~"){
                this->SetNonTerminals.erase(termianl.first);
            }
        }
    }
}
