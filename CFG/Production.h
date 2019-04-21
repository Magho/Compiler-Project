#ifndef COMPILERPROJECT_PRODUCTION_H
#define COMPILERPROJECT_PRODUCTION_H


#include <vector>
#include "ProductionElement.h"

class Production {
private:
    int DEBUG = 1;
public:
    void printProduction();
    vector<ProductionElement*> productionValue;
    vector<ProductionElement*> *getProductionVals();
    void appendNewProductionElement(ProductionElement* newProductionElement);
    vector<ProductionElement*> getProductionValue();
    void debugProduction();
    void debugProductionCFG();
};


#endif //COMPILERPROJECT_PRODUCTION_H
