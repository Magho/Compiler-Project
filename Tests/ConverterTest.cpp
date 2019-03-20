#include <iostream>
#include<vector>
#include<string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Converter.h"
#define EPSILON 163

using testing::Eq;
namespace {

    class ConverterTest : public testing::Test{
    public:
        ConverterTest();
    };

    ConverterTest::ConverterTest() {

    }
}

TEST_F(ConverterTest, Test1_ConacateOnly){
    stack<char> stack1;
    stack1.push('`');
    stack1.push('i');
    stack1.push('`');
    stack1.push('h');
    stack1.push('w');
    string label = "whi";
    map<string, stack<char>> map1;
    map1.insert(pair<string, stack<char>>(label,stack1));
    vector<string> labels;
    labels.emplace_back("whi");
    Converter converter;
    printf("\n");
    converter.regularExpressionToNFA(map1,labels).printCombinedNFA();
}

TEST_F(ConverterTest, Test2_Oronly){
    stack<char> stack1;
    stack1.push('|');
    stack1.push('b');
    stack1.push('a');
    string label = "id";
    map<string, stack<char>> map1;
    map1.insert(pair<string, stack<char>>(label,stack1));
    vector<string> labels;
    labels.emplace_back("id");
    Converter converter;
    printf("\n");
    converter.regularExpressionToNFA(map1,labels).printCombinedNFA();
}

TEST_F(ConverterTest, Test3_Or_Conc_Klenee){
    stack<char> stack1;
    stack1.push('`');
    stack1.push('*');
    stack1.push('|');
    stack1.push('B');
    stack1.push('A');
    stack1.push('|');
    stack1.push('1');
    stack1.push('0');
    string label = "id";
    map<string, stack<char>> map1;
    map1.insert(pair<string, stack<char>>(label,stack1));
    vector<string> labels;
    labels.emplace_back("id");
    Converter converter;
    printf("\n");
    converter.regularExpressionToNFA(map1,labels).printCombinedNFA();
}

TEST_F(ConverterTest, Test4_Or_Positive1){
    stack<char> stack1;
    stack1.push('+');
    stack1.push('|');
    stack1.push('b');
    stack1.push('a');
    string label = "id";
    map<string, stack<char>> map1;
    map1.insert(pair<string, stack<char>>(label,stack1));
    vector<string> labels;
    labels.emplace_back("id");
    Converter converter;
    printf("\n");
    converter.regularExpressionToNFA(map1,labels).printCombinedNFA();
}

TEST_F(ConverterTest, Test4_Or_Positive3){
    int nodeNumber = 0;
    stack<char> stack1;
    stack1.push('+');
    stack1.push('a');
    string label = "id";
    map<string, stack<char>> map1;
    map1.insert(pair<string, stack<char>>(label,stack1));
    vector<string> labels;
    labels.emplace_back("id");
    Converter converter;
    printf("\n");
    converter.regularExpressionToNFA(map1,labels).printCombinedNFA();
}

TEST_F(ConverterTest, Test4_Or_Positive2){
    int nodeNumber = 0;
    stack<char> stack1;
    stack1.push('`');
    stack1.push('*');
    stack1.push('|');
    stack1.push('b');
    stack1.push('a');
    stack1.push('|');
    stack1.push('b');
    stack1.push('a');
    string label = "id";
    map<string, stack<char>> map1;
    map1.insert(pair<string, stack<char>>(label,stack1));
    vector<string> labels;
    labels.emplace_back("id");
    Converter converter;
    printf("\n");
    converter.regularExpressionToNFA(map1,labels).printCombinedNFA();
}

TEST_F(ConverterTest, Test4_FuckIt){
    int nodeNumber = 0;
    stack<char> stack1;
    stack1.push('`');
    stack1.push('|');
    stack1.push('|');
    stack1.push('1');
    stack1.push('0');
    stack1.push('|');
    stack1.push('|');
    stack1.push('B');
    stack1.push('A');
    stack1.push('|');
    stack1.push('b');
    stack1.push('a');
    stack1.push('|');
    stack1.push('|');
    stack1.push('B');
    stack1.push('A');
    stack1.push('|');
    stack1.push('a');
    stack1.push('b');
    string label = "id";
    map<string, stack<char>> map1;
    map1.insert(pair<string, stack<char>>(label,stack1));
    vector<string> labels;
    labels.emplace_back("id");
    Converter converter;
    printf("\n");
    converter.regularExpressionToNFA(map1,labels).printCombinedNFA();
}