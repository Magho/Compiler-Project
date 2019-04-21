#include "FirstAndFollowLogic.h"

void FirstAndFollowLogic::calcFirstSet() {
    // create firstSets one for each non terminal
    for (auto rule : this->grammer->rules){
        Set *fs = new Set(rule.first);
        firstSets.insert(pair<string, Set*>(rule.first, fs));
    }
    // filling first set for each non terminal
    // iterate over non terminals from map
    for (auto rule : this->grammer->rules) {
        // for each non terminal iterate over its productions
        for(auto &production : *rule.second){
            int counter = 1;
            // in each production iterate over its production elements
            for(auto &productionElem : production->productionValue){
                // if first elem is terminal add it and break;
                if(productionElem->isTerminal()){
                    // add terminal
                    firstSets.at(rule.first)->SetTerminals.insert(
                            pair<string, ProductionElement*>(productionElem->getSymbolValue(),productionElem));
                    // add its production
                    firstSets.at(rule.first)->SetTerminalsProductions.insert(
                    pair<string, Production*>(productionElem->getSymbolValue(),production));
                    break;
                } else  {
                    // if non terminal add its first set to mine
                    // don't insert yourself
                    if(productionElem->getSymbolValue() != rule.first){
                        firstSets.at(rule.first)->SetNonTerminals.insert(
                                pair<string, Set*>(productionElem->getSymbolValue(),
                                                   firstSets.at(productionElem->getSymbolValue())));
                        // add its production
                        firstSets.at(rule.first)->SetNonTerminalsProductions.insert(
                                pair<string, Production*>(productionElem->getSymbolValue(),production));
                    }
                    if (!productionElem->hasEpsilon()){
                        // if not has epsilon break;
                        break;
                    }
                    // non terminal, has epsilon and last elem in the production so add epsilon to my first set
                    if (counter == production->productionValue.size()){
                        ProductionElement *productionElement = new ProductionElement (0, "~");
                        firstSets.at(rule.first)->SetTerminals.insert(
                                pair<string, ProductionElement*>(productionElement->getSymbolValue(),productionElement));
                        // no production for epsilon in case came from other non terminals
                    }
                }
                counter++;
            }
        }
    }
    // make each first set finish it self --> convert each first set it has to terminals
    cout << "-------------------------------------- First sets ----------------------------------------------------- ";
    for(auto firstSet : firstSets){
        firstSet.second->finishMySet(false);
        cout << endl;
        cout << "terminal set ";
        cout << firstSet.first << " : ";
        firstSet.second->printSetTerminals();
        cout << endl;
        cout << "terminal productions ";
        cout << firstSet.first << " : ";
        firstSet.second->printSetTerminalsProductions();
        cout << "non terminal set ";
        cout << firstSet.first << " : ";
        firstSet.second->printSetNonTerminals();
        cout << endl;
    }
    cout << "-------------------------------------- First sets ----------------------------------------------------- ";
}

void FirstAndFollowLogic::calcFollowtSet() {

    // create followSets one for each non terminal
    for (auto rule : this->grammer->rules){
        Set *fs = new Set(rule.first);
        // add $ to start non terminals
        if(rule.first == this->grammer->startingProductionElement->getSymbolValue()){
            ProductionElement *productionElement = new ProductionElement (0, "$");
            fs->SetTerminals.insert(pair<string ,ProductionElement*>(productionElement->getSymbolValue(),productionElement));
        }
        followSets.insert(pair<string, Set*>(rule.first, fs));
    }

    // filling follow set for each non terminal
    // iterate over non terminals from map
    for (auto outerRule : this->grammer->rules) {
        for (auto rule : this->grammer->rules) {
            // for each non terminal iterate over its productions
            for (auto &production : *rule.second) {
                // in each production iterate over its production elements
                for (int i = 0; i < production->productionValue.size(); ++i) {
                    // found in right hand side
                    if (production->productionValue[i]->getSymbolValue() == outerRule.first){
                        // not last element
                        if(i < production->productionValue.size()-1){
                            // element after it is terminal add it
                            if(production->productionValue[i+1]->isTerminal()){
                                followSets.at(outerRule.first)->SetTerminals.insert(pair<string, ProductionElement*>
                                        (production->productionValue[i+1]->getSymbolValue(),production->productionValue[i+1]));
                            } else {
                                // element after it is non terminal add its firstSet
                                // TODO 1.1
                                for (auto terminal : firstSets.at(production->productionValue[i + 1]->getSymbolValue())->SetTerminals){
                                    // if exist before just rewrite it
                                    // add terminal
                                    followSets.at(outerRule.first)->SetTerminals.insert(pair<string ,ProductionElement*> (terminal.first, terminal.second));
                                    // add its production if finishing first set
                                }
                                // if element after me is non terminal, last element and go to epsilon
                                if (production->productionValue[i + 1]->hasEpsilon() && i + 1 == production->productionValue.size()-1) {
                                    followSets.at(outerRule.first)->SetNonTerminals.insert(
                                            pair<string, Set *>(rule.first, followSets.at(rule.first)));
                                    followSets.at(outerRule.first)->NonTerminalNamesInFollowSet.push_back(rule.first);
                                    break;
                                } else {
                                    // element after it is non terminal, has epsilon production and not last element
                                    while (i + 2 < production->productionValue.size() &&
                                           production->productionValue[i + 1]->hasEpsilon()) {
                                        i++;
                                        // don't add yourself
                                        //TODO 1.2
                                        for (auto terminal : firstSets.at(production->productionValue[i + 1]->getSymbolValue())->SetTerminals){
                                            // if exist before just rewrite it
                                            // add terminal
                                            followSets.at(outerRule.first)->SetTerminals.insert(pair<string ,ProductionElement*> (terminal.first, terminal.second));
                                            // add its production if finishing first set
                                        }
                                        // same check as before
                                        if (production->productionValue[i + 1]->hasEpsilon() && i + 1 == production->productionValue.size()-1) {
                                            followSets.at(outerRule.first)->SetNonTerminals.insert(
                                                    pair<string, Set *>(rule.first, followSets.at(rule.first)));
                                            followSets.at(outerRule.first)->NonTerminalNamesInFollowSet.push_back(rule.first);
                                            break;
                                        }
                                    }
                                }
                            }
                            // last element add follow of the left hand side to my follow
                        } else {
                            followSets.at(outerRule.first)->SetNonTerminals.insert(
                                    pair<string, Set*>(rule.first, followSets.at(rule.first)));
                        }
                    }
                }
            }
        }
    }
    // make each follow set finish it self --> convert each first set it has to terminals
    cout << endl;
    cout << "-------------------------------------- Follow sets ----------------------------------------------------- ";
    for(auto followSet : this->followSets){
        followSet.second->finishMySet(true);
        cout << endl;
        cout << "terminal set ";
        cout << followSet.first << " : ";
        followSet.second->printSetTerminals();
        cout << endl;
        cout << "non terminal set ";
        cout << followSet.first << " : ";
        followSet.second->printSetNonTerminals();
        cout << endl;
    }
    cout << "-------------------------------------- Follow sets ----------------------------------------------------- ";
}
//map<string, vector<ProductionElement>> FirstAndFollowLogic::getFirsttSet() {
//    map<string, vector<ProductionElement>> result;
//    for(auto firstSet : firstSets){
//        vector<ProductionElement> productionElements;
//        for (auto terminal : firstSet.second->SetTerminals){
//            productionElements.push_back(*terminal.second);
//        }
//        result.insert(pair<string, vector<ProductionElement>> (firstSet.first, productionElements));
//    }
//    return result;
//}
//
//map<string, vector<ProductionElement>> FirstAndFollowLogic::getFollowtSet() {
//    map<string, vector<ProductionElement>> result;
//    for(auto followSet : followSets){
//        vector<ProductionElement> productionElements;
//        for (auto terminal : followSet.second->SetTerminals){
//            productionElements.push_back(*terminal.second);
//        }
//        result.insert(pair<string, vector<ProductionElement>> (followSet.first, productionElements));
//    }
//    return result;
//}
