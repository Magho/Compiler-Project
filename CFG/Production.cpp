#include <iostream>
#include <string>
#include "Production.h"
void Production::printProduction() {

    for(ProductionElement *e : productionValue){
        std::cout<<e->getSymbolValue()<<"{"<<(e->isTerminal() ? "T} ":"N} ");
    }
    std::cout<<endl;

}

vector<ProductionElement*> *Production::getProductionVals(){
    return  &productionValue;


}

void Production::appendNewProductionElement(ProductionElement* newProductionElement) {
    productionValue.push_back(newProductionElement);
}
vector<ProductionElement*> Production::getProductionValue() {
    return productionValue;
}
void Production::debugProduction() {
    if(DEBUG) {
//        cout << "value of production is ";
        for (auto i : productionValue) {
            cout << i->getSymbolValue();
        }
//        cout << endl;
    }
}

void Production::debugProductionCFG() {
    if(DEBUG) {
        for (auto i : productionValue) {
            cout << i->getSymbolValue();
        }
        cout << endl;
    }
}