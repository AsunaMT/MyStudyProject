#include "Caculator.h"

Caculator::Caculator(){
    map<string, int> temp = {
        {"1", 0}, {"2", 0}, {"3", 0}, {"4", 0}, {"5", 0},
        {"6", 0}, {"7", 0}, {"8", 0}, {"9", 0}, {"0", 0}, {".", 0},
        {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"%", 2}, {"+", 2}, {"^", 3},
        {"sin", 10}, {"cos", 10}, {"tan", 10}, {"lg", 10}, {"ln", 10}, {"!", 10},
        {"arcsin", 10}, {"arccos", 10}, {"arctan", 10},
        {"sinh", 10}, {"cosh", 10}, {"tanh", 10},
        {"(", -1}, {"[", -1}, {"{", -1}, {")", -2}, {"]", -2}, {"}", -2}
    };
    priority = temp;
}
string Caculator::ToPostfixExpression(string formula){
    string result;
    for(int i = 0; i < formula.size(); i++){
        int len = 1;
        if(formula[i] >= 'a' && formula[i] <= 'z'){
            int j = i + 1;
            while(j < formula.size() && formula[j] >= 'a' && formula[j] <= 'z'){ len ++; j ++; }
        }//处理单目运算符或字母串
        int temp = priority[formula.substr(i, len)];
        if(!temp || (formula[i] == '-' && (stack.Empty() || priority[stack.GetTop()] < 0))){
            int j = i + 1;
            while(j < formula.size() && !priority[formula.substr(j++, 1)]){ len ++; }
            result.assign(result + formula.substr(i, len) + " " );
            i += len-1;
            continue;                                             
        }//处理数字(正/负)
        if(temp < -1){
            while(priority[stack.GetTop()] > 0){
                result.assign(result + stack.GetTop() + " ");
                stack.Pop();
            }
            stack.Pop();
            continue;
        }//处理后括号
        if(stack.Empty() || temp > priority[stack.GetTop()] || temp < 0) {
            stack.Push(formula.substr(i, len));
            i += len - 1;
            continue;
        }
        while(!stack.Empty() && temp <= priority[stack.GetTop()]){
            result.assign(result + stack.GetTop() + " ");
            stack.Pop();
        }
        stack.Push(formula.substr(i, len));
        i += len - 1;
    }
    while(!stack.Empty()){
        result.assign(result + stack.GetTop() + " ");
        stack.Pop();
    }
    return result;
}

double Caculator::Compute(string formula){
    formula.assign(ToPostfixExpression(formula));
    for(int i = 0; i < formula.size(); i += 2){
        int len = 0;
        for(int j = i; j < formula.size() && formula[j] != ' ' && formula[j] != '\0'; j ++){ len ++; }
        string temp(formula.substr(i, len)); 
        if(priority[temp] == 10){
            HandleUnaryOperators(temp);
            i += len -1;
            continue;
        }
        string tempChar(formula.substr(i + len - 1, len));
        switch(priority[tempChar]){
            case 0:
                stack.Push(temp);
                break;
            case 1: case 2: case 3:
                double a = atof(stack.Pop().c_str()); 
                double b = atof(stack.Pop().c_str());
                switch(tempChar[0]){
                    case '+':
                    stack.Push(to_string(a + b));   break;
                    case '-':
                    stack.Push(to_string(b - a));   break;
                    case '*':
                    stack.Push(to_string(a * b));   ;break;
                    case '/':
                    stack.Push(to_string(b / a));    break;
                    case '%':
                    stack.Push(to_string((int)b % (int)a));    break;
                    case '^':
                    stack.Push(to_string(pow(b, a)));  break;
                }
                break;
        } 
        i += len - 1;
    }
    return atof(stack.Pop().c_str());
}

void Caculator::HandleUnaryOperators(string &temp){
    if(temp == "sin")   stack.Push(to_string(sin(atof(stack.Pop().c_str()))));
    if(temp == "cos")   stack.Push(to_string(cos(atof(stack.Pop().c_str()))));
    if(temp == "tan")   stack.Push(to_string(tan(atof(stack.Pop().c_str()))));
    if(temp == "arcsin")    stack.Push(to_string(asin(atof(stack.Pop().c_str()))));
    if(temp == "arccos")    stack.Push(to_string(acos(atof(stack.Pop().c_str()))));
    if(temp == "arctan")    stack.Push(to_string(atan(atof(stack.Pop().c_str()))));
    if(temp == "sinh")  stack.Push(to_string(sinh(atof(stack.Pop().c_str()))));
    if(temp == "cosh")  stack.Push(to_string(cosh(atof(stack.Pop().c_str()))));
    if(temp == "tanh")  stack.Push(to_string(tanh(atof(stack.Pop().c_str()))));
    if(temp == "ln")    stack.Push(to_string(log(atof(stack.Pop().c_str()))));
    if(temp == "lg")    stack.Push(to_string(log10(atof(stack.Pop().c_str()))));
    if(temp == "!"){
        int n = atoi(stack.Pop().c_str());
        int buf = 1;
        for(int i = 2; i <= n; i ++){
            buf *= i;
        }
        stack.Push(to_string(buf));
    }  
}