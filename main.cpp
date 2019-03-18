#include <gtest/gtest.h>
#include <gmock/gmock.h>

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    return 0;
}

//#include <iostream>
//#include<vector>
//#include<string>
//#include "Converter.h"
//#define EPSILON 163
//
//using namespace std;
//int main() {
//    stack<char> stack1;
//    stack1.push('+');
//    stack1.push('|');
//    stack1.push('b');
//    stack1.push('a');
//    string label = "id";
//    map<string, stack<char>> map1;
//    map1.insert(pair<string, stack<char>>(label,stack1));
//    vector<string> labels;
//    labels.emplace_back("id");
//    Converter converter;
//    printf("\n");
//    converter.regularExpressionToNFA(map1,labels).printCombinedNFA();
//    return 0;
//}