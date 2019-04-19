//
// Created by ecc on 19/04/2019.
//

#ifndef COMPILERPROJECT_PRODUCTION_H
#define COMPILERPROJECT_PRODUCTION_H


#include <vector>
#include "ProductionElement.h"

class Production {
public://TODO
    int DEBUG = 1;
    vector<ProductionElement*> productionValue;
    void appendNewProductionElement(ProductionElement* newProductionElement);
    vector<ProductionElement*> getProductionValue();
    void debugProduction();
    void debugProductionCFG();
};


#endif //COMPILERPROJECT_PRODUCTION_H