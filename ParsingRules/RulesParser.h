#ifndef COMPILERPROJECT_RULESPARSER_H
#define COMPILERPROJECT_RULESPARSER_H
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <stack>
using namespace std;
#define EPSILON (char)163
#define ADDITION (char)200
#define MULTIPLICATION (char)201
#define OR (char)202
class RulesParser {
private:
    int debug = 0;
    unordered_map<string, string> definitions;
    unordered_map<string, string> expressions;
    unordered_map<string, string> keywords;
    unordered_map<string, string> punctuations;
    unordered_map<string, vector<char>> regularExpressionPostfixes;
    unordered_map<string, stack<char>> regexPostfix;
    vector<string> orderOfLabels;

    int getIndexOf(string str, char x);
    void debugMap(unordered_map<string, string> map, string mapName);
    void debugMap(unordered_map<string, vector<char>> map, string mapName);
    void debugVector(vector<string> v, string vectorName);
    void debugMap(unordered_map<string, stack<char>> map, string mapName);
    string trim(string &str);
    vector<string> split(string str, char deli);
    stack<char> convertVecToStack(vector<char> v);

private:
    int isSpecialChar(char x);
    int isSpecialChar(string str, int i);
    int isConcatenated(string str, int i);
    void removeCharFromAndNotFollowedBy(string &str, char c, char f);
    void replaceAllEpsilon(string &str, string w);
    int isRegularDefinition (string expr);
    int isRegularExpression(string expr);
    int isKeyword(string expr);
    int isPunctuation(string expr);
    void handleRange(string &expr);
    void handleLabels(string &expr);
    void handleSpecialChar(string &expr);
    void handleRegularDefinition(string definition);
    void handleRegularExpression(string expression);
    void handleKeywords(string set);
    void handlePunctuation(string set);
    int compOperator(char op1, char op2);
    void handleInsertOperator(vector<char> &operators, vector<char> &postfix, char op);
    void handleInsertOperand(vector<char> &postfix,string &expr, int i);
    void handleExpressionMap();
    void handleKeywordMap();
    void handlePunctuationMap();
    void fillRegularExpressionsPostfix();
public:
    unordered_map<string, stack<char>> getRegularExpressionPostfixes(string file);
    vector<string> getLabelsOrdered();
};


#endif //COMPILERPROJECT_RULESPARSER_H
