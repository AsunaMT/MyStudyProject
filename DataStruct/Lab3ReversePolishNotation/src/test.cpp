#include <iostream>
#include "Caculator.h"
using namespace std;

int main(){
    Caculator c;
    cout << "For example :" << endl;
    cout << "(6+5+6)*7^8 = "<< c.ToPostfixExpression("(6+5+6)*7^8") << " = ";
    cout << c.Compute("(6+5+6)*7^2") << endl;
    cout << "6+(5+6*7) = "<< c.ToPostfixExpression("6+(5+6*7)") << " = ";
    cout << c.Compute("6+(5+6*7)") << endl;
    cout << "-6+(-5+6.5*(-7)) = " << c.ToPostfixExpression("-6+(-5+6.5*(-7))") << " = ";
    cout << c.Compute("-6+(-5+6.5*(-7))") << endl;
    cout << "6!+sin(5+6*7) = " << c.ToPostfixExpression("6!+sin(5+6*7)") << " = ";
    cout << c.Compute("6!+sin(5+6*7)") << endl;
    cout << "6+ln[(542+65)*87] = " << c.ToPostfixExpression("6+ln[(542+65)*87]") << " = ";
    cout << c.Compute("6+ln[(542+65)*87]") << endl;
    cout << "65%7+6/8 = "<< c.ToPostfixExpression("65%7+6/8") << " = ";
    cout << c.Compute("65%7+6/8") << endl;
    cout << "lg[(6+5!)*7^2]^cos{2*[70/(30+40)]} = "<< c.ToPostfixExpression("lg[(6+5!)*7^2]^cos{2*[70/(30+40)]}") << " = ";
    cout << c.Compute("lg[(6+5!)*7^2]^cos{2*[70/(30+40)]}") << endl;
    cout << "arctan(5^4-10)+tanh(5/9)^2*12 = "<< c.ToPostfixExpression("arctan(5^4-10)+tanh(5/9)^2*12") << " = ";
    cout << c.Compute("(arctan(5^4-10)+tanh(5/9)^2*12") << endl;
    while(1){
        cout << "Please input: " << endl;   
        string f;
        cin >> f;
        cout << f << " = " << c.ToPostfixExpression(f) << " = " << c.Compute(f) << endl; 
    }
    return 0;
}
