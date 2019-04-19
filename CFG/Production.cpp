//
// Created by ecc on 19/04/2019.
//

#include "Production.h"
void Production::appendNewProductionElement(ProductionElement* newProductionElement) {
    productionValue.push_back(newProductionElement);
}
vector<ProductionElement*> Production::getProductionValue() {
    return productionValue;
}
void Production::debugProduction() {
    if(DEBUG) {
        cout << "value of production is ";
        for (auto i : productionValue) {
            cout << i->getSymbolValue();
        }
        cout << endl;
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