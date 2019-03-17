#include "RulesParser.h"
int RulesParser::getIndexOf(string str, char x) {
    for (int i = 0; i < str.length(); ++i) {
        if(str[i] == x) {
            return i;
        }
    }
    return -1;
}
void RulesParser::debugMap(unordered_map<string, string> map, string mapName) {
    cout << mapName << ":" << endl;
    for(auto i : map) {
        cout << "Label: " << i.first << ", Value: " << i.second << endl;
    }
    cout << "End of " << mapName << "." << endl;
}
void RulesParser::debugMap(unordered_map<string, vector<char>> map, string mapName) {
    cout << mapName << ":" << endl;
    for(auto i : map) {
        cout << "Label: " << i.first << ", Value: ";
        for (auto j : i.second) {
            cout << j << " ";
        }
        cout << endl;
    }
    cout << "End of " << mapName << "." << endl;
}
void RulesParser::debugVector(vector<string> v, string vectorName) {
    cout << vectorName << ":" << endl;
    for(auto i : v) {
        cout << i << endl;
    }
    cout << "End of " << vectorName << "." << endl;
}
string RulesParser::trim(string &str)
{
    int i = 0, j = 0;
    while (str[i])
    {
        if (str[i] != ' ')
            str[j++] = str[i];
        i++;
    }
    str[j] = '\0';
    str.erase(j, i - j);
    return str;
}

vector<string> RulesParser::split(string str, char deli) {
    int deliIndex = getIndexOf(str, deli);
    vector<string> splitResult;
    splitResult.push_back(str.substr(0, deliIndex));
    splitResult.push_back(str.substr(deliIndex + 1, str.length() - 1));
    for (int i = 0; i < splitResult.size(); ++i) {
        trim(splitResult[i]);
    }
    if(debug) {
        cout << "Split: " << str << " around " << deli << " Result>>";
        for (string i : splitResult) {
            cout << i << " ";
        }
        cout << endl;
    }
    return splitResult;
}
int RulesParser::isSpecialChar(char x) {
    return x == '|' || x == '*' || x == '+' || x == '(' || x == ')';
}

int RulesParser::isSpecialChar(string str, int i) {
    if(str[i] == '|' || str[i] == '*' || str[i] == '+' || str[i] == '(' || str[i] == ')') {
        return i == 0 || str[i - 1] != '\\';
    }
    return 0;
}
int RulesParser::isConcatenated(string str, int i) {
    if(str[i] == '(') {
        return i != 0 && str[i - 1] != '|' && str[i - 1] != '(';
    }
    return 0;
}
void RulesParser::removeCharFromAndNotFollowedBy(string &str, char c, char f) {
    for (int i = 0; i < str.length(); ++i) {
        if(str[i] == c && (i == str.length() - 1 || (str[i + 1] != f && !isSpecialChar(str[i + 1])))) {
            str.erase(i,1);
            i--;
        }
    }
}

void RulesParser::replaceAllEpsilon(string &str, string w) {
    for (int i = 0; i < str.length(); ++i) {
        if(str[i] == '\\' && i < str.length() - 1 && str[i + 1] == 'L') {
            str.erase(i,2);
            str.insert(i, w);
            i--;
        }
    }
}

int RulesParser::isRegularDefinition (string expr) {
    for (int i = 0; i < expr.length(); ++i) {
        if (expr[i] == '=') {
            if(expr[i - 1] != '\\') {
                if(debug) {
                    cout << expr << " is regular definition." << endl;
                }
                return 1;
            }
        }
    }
    return 0;
}

int RulesParser::isRegularExpression(string expr) {
    for (int i = 0; i < expr.length(); ++i) {
        if (expr[i] == ':') {
            if(expr[i - 1] != '\\') {
                if(debug) {
                    cout << expr << " is regular expression." << endl;
                }
                return 1;
            }
        }
    }
    return 0;
}

int RulesParser::isKeyword(string expr) {
    if(expr[0] == '{' && expr[expr.length() - 1] == '}') {
        if(debug) {
            cout << expr << " are keywords." << endl;
        }
        return 1;
    }
    return 0;
}

int RulesParser::isPunctuation(string expr) {
    if(expr[0] == '[' && expr[expr.length() - 1] == ']') {
        if(debug) {
            cout << expr << " are punctuations." << endl;
        }
        return 1;
    }
    return 0;
}

void RulesParser::handleRange(string &expr) {
    if(debug) {
        cout << "Handling Range in " << expr;
    }
    int rangeIndex = getIndexOf(expr, '-');
    while( rangeIndex != -1 && expr[rangeIndex - 1] != '\\') {
        char rangeBegin = expr[rangeIndex - 1];
        char rangeEnd = expr[rangeIndex + 1];
        expr.erase(rangeIndex - 1, 3);
        expr.insert(rangeIndex - 1, 1,')');
        for (char i = rangeEnd; i >= rangeBegin; i--) {
            expr.insert(rangeIndex - 1, 1, i);
            if(i != rangeBegin) {
                expr.insert(rangeIndex - 1, 1, '|');
            }
        }
        expr.insert(rangeIndex - 1, 1,'(');
        rangeIndex = getIndexOf(expr, '-');
    }
    if(debug) {
        cout << " Result in " << expr << endl;
    }
}

void RulesParser::handleLabels(string &expr) {
    if(debug) {
        cout << "Handle Labels for " << expr << " Result in ";
    }
    for(auto label : definitions) {
        int labelPosition = expr.find(label.first);
        if(labelPosition == string::npos) {
            continue;
        }
        while (labelPosition != string::npos) {
            expr.erase(labelPosition, label.first.length());
            expr.insert(labelPosition, label.second);
            labelPosition = expr.find(label.first);
        }
    }
    if(debug) {
        cout << expr << endl;
    }
}

void RulesParser::handleSpecialChar(string &expr) {
    if(debug) {
        cout << "Handling special characters in " << expr << " Result in ";
    }
    removeCharFromAndNotFollowedBy(expr, '\\', 'L');

    string epsilonString;
    epsilonString.push_back(EPSILON);
    replaceAllEpsilon(expr, epsilonString);
    if(debug) {
        cout << expr << endl;
    }
}

void RulesParser::handleRegularDefinition(string definition) {
    vector<string> twoHandSide = split(definition, '=');
    handleRange(twoHandSide[1]);
    handleLabels(twoHandSide[1]);
    handleSpecialChar(twoHandSide[1]);
    if(definitions.count(twoHandSide[0]) > 0) {
        cout << "ERROR: multiple definition of same label (" << twoHandSide[0] << ")" << endl;
    }
    twoHandSide[1].insert(0, "(");
    twoHandSide[1].insert(twoHandSide[1].length() - 1, ")");
    definitions[twoHandSide[0]] = twoHandSide[1];
}



void RulesParser::handleRegularExpression(string expression) {
    vector<string> twoHandSide = split(expression, ':');
    orderOfLabels.push_back(twoHandSide[0]);
    handleRange(twoHandSide[1]);
    handleLabels(twoHandSide[1]);
    handleSpecialChar(twoHandSide[1]);
    if(expressions.count(twoHandSide[0]) > 0) {
        cout << "ERROR : multiple definition of same label (" << twoHandSide[0] << ")" << endl;
    }
    twoHandSide[1].insert(twoHandSide[1].length(), ")");
    twoHandSide[1].insert(0, "(");
    expressions[twoHandSide[0]] = twoHandSide[1];
}

void RulesParser::handleKeywords(string set) {
    int keywordFound = 0, keywordIndex = -1;
    for (int i = 0; i < set.length(); ++i) {
        if(set[i] == '{') {
            continue;
        }
        if(set[i] == '}') {
            break;
        }
        if(set[i] != ' ' && !keywordFound) {
            keywordFound = 1;
            keywordIndex = i;
        } else if(set[i] == ' ' && keywordFound) {
            string keyword = set.substr(keywordIndex, i - keywordIndex);
            orderOfLabels.push_back(keyword);
            keywords[keyword] = keyword;
            keywordFound = 0;
            keywordIndex = -1;
        }
    }
}

void RulesParser::handlePunctuation(string set) {
    int symbolFound = 0, symbolIndex = -1;
    for (int i = 0; i < set.length(); ++i) {
        if(set[i] == '[' && (i == 0 || set[i - 1] != '\\')) {
            continue;
        }
        if(set[i] == ']' && set[i - 1] != '\\') {
            if(symbolFound) {
                string symbol = set.substr(symbolIndex, i - symbolIndex);
                orderOfLabels.push_back(symbol);
                punctuations[symbol] = symbol;
            }
            break;
        }
        if(set[i] == '\\' && set[i + 1] != ' ') {
            continue;
        }
        if(set[i] != ' ' && !symbolFound) {
            symbolFound = 1;
            symbolIndex = i;
        } else if(set[i] == ' ' && symbolFound) {
            string symbol = set.substr(symbolIndex, i - symbolIndex);
            orderOfLabels.push_back(symbol);
            punctuations[symbol] = symbol;
            symbolFound = 0;
            symbolIndex = -1;
        }
    }
}
int RulesParser::compOperator(char op1, char op2) {
    if(op2 == ')') {
        return 2;
    } else if(op1 == op2 && op1 != '(') {
        return 1;
    } else if (op1 == '`' && op2 == '|') {
        return 1;
    } else if(op1 == '(' && (op2 == '|' || op2 == '`')) {
        return 0;
    } else if(op1 == '|' && op2 == '`') {
        return 0;
    } else if(op1 == '|' && op2 == '(') {
        return 0;
    } else if(op1 == '`' && op2 == '(') {
        return 0;
    } else if(op1 == '(' && op2 == '(') {
        return 0;
    } else {
        cout << op1 << " and " << op2 << " are not handled cases." << endl;
        return 0;
    }
}
void RulesParser::handleInsertOperator(vector<char> &operators, vector<char> &postfix, char op) {
    if(op == '*' || op == '+') {
        postfix.push_back(op);
    } else if(!operators.empty()) {
        if(!operators.empty() && compOperator(operators.back(), op) == 1) {
            while(!operators.empty() && compOperator(operators.back(), op) == 1) {
                postfix.push_back(operators.back());
                operators.pop_back();
            }
            operators.push_back(op);
        } else if(!operators.empty() && compOperator(operators.back(), op) == 2) {
            while(!operators.empty()&& operators.back() != '(') {
                postfix.push_back(operators.back());
                operators.pop_back();
            }
            operators.pop_back();
        } else if(!operators.empty() && compOperator(operators.back(), op) == 0) {
            operators.push_back(op);
        }
    } else {
        operators.push_back(op);
    }
}

void RulesParser::handleInsertOperand(vector<char> &postfix,string &expr, int i) {
    if(expr[i] == '\\') {
        expr.erase(i, 1);
    }
    if(expr[i] == '+') {
        expr[i] = ADDITION;
    } else if(expr[i] == '*') {
        expr[i] = MULTIPLICATION;
    } else if(expr[i] == '|') {
        expr[i] = OR;
    }
    postfix.push_back(expr[i]);
}
void RulesParser::handleExpressionMap() {
    for(auto expression : expressions) {
        if(debug) {
            cout << "Handle expression map" << expression.second << endl;
        }
        string label = expression.first;
        string exprValue = expression.second;
        vector<char> operators;
        vector<char> postfix;
        for (int i = 0; i < exprValue.length(); ++i) {
            if(isSpecialChar(exprValue, i)) {
                if(isConcatenated(exprValue, i)) {
                    handleInsertOperator(operators, postfix, '`');
                }
                handleInsertOperator(operators, postfix, exprValue[i]);
            } else {
                if(i > 0 && exprValue[i - 1] != '|' && exprValue[i - 1] != '(') {
                    handleInsertOperator(operators, postfix, '`');
                }
                handleInsertOperand(postfix, exprValue, i);
            }
        }

        while(!operators.empty()) {
            postfix.push_back(operators.back());
            operators.pop_back();
        }
        regularExpressionPostfixes[label] = postfix;
        if(debug) {
            cout << "Operands of expr: " << exprValue << " are ";
            for (auto i : postfix) {
                cout << i << " ";
            }
            cout << endl;
        }
    }
}
void RulesParser::handleKeywordMap() {
    for(auto keyword : keywords) {
        if(debug) {
            cout << "Handle keyword map " << keyword.second << endl;
        }
        string label = keyword.first;
        string exprValue = keyword.second;
        vector<char> operators;
        vector<char> postfix;
        for (int i = 0; i < exprValue.length(); ++i) {
            if(i > 0) {
                handleInsertOperator(operators, postfix, '`');
            }
            handleInsertOperand(postfix, exprValue, i);
        }

        while(!operators.empty()) {
            postfix.push_back(operators.back());
            operators.pop_back();
        }
        regularExpressionPostfixes[label] = postfix;
        if(debug) {
            cout << "Operands of expr: " << exprValue << " are ";
            for (auto i : postfix) {
                cout << i << " ";
            }
            cout << endl;
        }
    }
}
void RulesParser::handlePunctuationMap() {
    for(auto punctuation : punctuations) {
        if(debug) {
            cout << "Handle punctuation map " << punctuation.second << endl;
        }
        string label = punctuation.first;
        vector<char> postfix;
        postfix.push_back(punctuation.second[0]);
        regularExpressionPostfixes[label] = postfix;
        if(debug) {
            cout << "Operands of expr: " << punctuation.second[0] << " are ";
            for (auto i : postfix) {
                cout << i << " ";
            }
            cout << endl;
        }
    }
}
void RulesParser::fillRegularExpressionsPostfix() {
    handleExpressionMap();
    handleKeywordMap();
    handlePunctuationMap();
}
unordered_map<string, vector<char>> RulesParser::getRegularExpressionPostfixes(string file) {
    ifstream rules_file(file);
    string line;
    while(getline(rules_file, line)) {
        if(isRegularDefinition(line)) {
            handleRegularDefinition(line);
        } else if(isRegularExpression(line)) {
            handleRegularExpression(line);
        } else if(isKeyword(line)) {
            handleKeywords(line);
        } else if(isPunctuation(line)) {
            handlePunctuation(line);
        } else {
            cout << line << " is undefined!!" << endl;
        }
    }
    if(debug) {
        debugMap(definitions, "Definitions");
        debugMap(expressions, "Expressions");
        debugMap(keywords, "Keywords");
        debugMap(punctuations, "Punctuations");
    }
    fillRegularExpressionsPostfix();
    if(debug) {
        debugMap(regularExpressionPostfixes, "Regular Expression Postfixes");
    }
    return regularExpressionPostfixes;
}
vector<string> RulesParser::getLabelsOrdered() {
    return orderOfLabels;
}
