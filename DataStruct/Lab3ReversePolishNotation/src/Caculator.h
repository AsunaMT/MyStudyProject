#ifndef CACULATOR_H
#define CACULATOR_H
#include "Stack.cpp"
#include <string>
#include <map>
using namespace std;

class Caculator{
    Stack<string> stack;
    map<string, int>  priority;
    void HandleUnaryOperators(string &op);
public:
    Caculator();
    string ToPostfixExpression(string formula);
    double Compute(string formula);
};

#endif