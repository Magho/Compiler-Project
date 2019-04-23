//
// Created by ecc on 19/04/2019.
//

#include "GrammarParser.h"

GrammarParser::GrammarParser(string inputFile) {
    ifstream rules_file(inputFile);
    string line;
    string currentNonTerminal;
    while(getline(rules_file, line)) {
        cout << line << endl;
        if(line[0] == '#') {
            getStringUntil(line, " ");
            currentNonTerminal = getStringUntil(line, "=");
            trim(currentNonTerminal, " =");
            getStringUntil(line, " ");
            ProductionElement* newProductionElement;
            if(!startingDetected) {
                startingDetected = 1;
                grammar.createStartingSymbol(currentNonTerminal);
            } else {
                grammar.createNewNonTerminal(currentNonTerminal);
            }
            while(line.length() != 0) {
                string production = getStringUntil(line,"|");
                trim(production, "|");
                Production* newP = handleProductionString(production);
                grammar.assignProductionToNonTerminal(newP, currentNonTerminal);
                handleEpsilonProduction(newP, currentNonTerminal);
            }
        } else if(line[0] == '|') {
            getStringUntil(line, "|");
            while(line.length() != 0) {
                string production = getStringUntil(line,"|");
                trim(production, "|");
                Production* newP = handleProductionString(production);
                grammar.assignProductionToNonTerminal(newP, currentNonTerminal);
                handleEpsilonProduction(newP, currentNonTerminal);
            }
        } else {
            if(DEBUG) {
                cout << "ERROR: " << line <<  " isn't recognized as input.";
            }
        }
    }
    grammar.debug();
}

Production* GrammarParser::handleProductionString(string p) {
    Production* production = new Production();
    while(p.length() != 0) {
        string newProductionElementStr = getStringUntil(p, " ");
        trim(newProductionElementStr, " ");
        if(newProductionElementStr.length() == 0) {
            continue;
        }
        ProductionElement* newPE;
        if(newProductionElementStr.find('\'') != string::npos) {
            trim(newProductionElementStr, "'");
            newPE = grammar.createNewTerminal(newProductionElementStr);
        } else {
            newPE = grammar.createNewNonTerminal(newProductionElementStr);
        }
        production->appendNewProductionElement(newPE);
    }
    return production;
}

string GrammarParser::getStringUntil(string &str, string x) {
    if(DEBUG) {
        cout << "Getting string from " <<  str << " until " << x << " is found." << endl;
    }
    for(int i = 0; i < str.length(); i++) {
        if(x.find(str[i]) != x.npos  && (i == 0 || str[i - 1] != '\\' || str[i - 1] != '\'')) {
            string result = str.substr(0, i + 1);
            str.erase(0, i + 1);
            if(DEBUG) {
                cout << "result is " << result << "." << endl;
            }
            return result;
        }
    }
    if(DEBUG) {
        cout << "result is " << str << "." << endl;
    }
    string result = str;
    str.erase(0, str.length());
    return result;
}

string GrammarParser::trim(string &str, string deli)
{
    if(DEBUG) {
        cout << "Trimming " << str << "..." << endl;
    }
    int i = 0, j = 0;
    while (str[i])
    {
        if (deli.find(str[i]) == deli.npos)
            str[j++] = str[i];
        i++;
    }
    str[j] = '\0';
    str.erase(j, i - j);
    if(DEBUG) {
        cout << "Result of trimming is " << str << "." <<endl;
    }
    return str;
}

CFG GrammarParser::getGrammar() {
    return grammar;
}

void GrammarParser::handleEpsilonProduction(Production *p, string nonTerminal) {
    if(DEBUG) {
        cout << "Handling epsilon transition of " << nonTerminal << " for production: ";
        p->debugProductionCFG();
    }
    for(auto i : p->getProductionValue()) {
        if(i->getSymbolValue() == CFGEPSILON) {
            if(DEBUG) {
                cout << "The non-terminal " << nonTerminal << " has epsilon production." << endl;
            }
            ProductionElement* productionElementHasEpsilon = grammar.getProductionElement(nonTerminal, 0);
            productionElementHasEpsilon->gotEpsilon = true;
            return;
        }
    }
    if(DEBUG) {
        cout << "The non-terminal " << nonTerminal << " doesn't have epsilon production." << endl;
    }
}