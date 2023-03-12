#include "StudentHash.h"
#include <iostream>

using namespace std;

int main(){
    StuHash s;
    s.ReadinCSV("data.csv");
    cout << "Æ½¾ùËÑË÷Ê±¼ä:" << s.hashFunTimes / 149.0 << endl;
    cout << "ËÑË÷Ê¾Àý£º" << endl;
    StuInf a = s.Search("Öì¶¬Ã·");
    cout << a.name << ":" << a.stuNum << a.gender << a.age << "Ëê" << a.phoneNum << endl;
    a = s.Search("°×Ï¼");
    cout << a.name << ":" << a.stuNum << a.gender << a.age << "Ëê" << a.phoneNum << endl;
    cout << "É¾³ýÊ¾Àý£º" << endl;
    s.Delete("°×Ï¼"); 
    cout << "ÒÑÉ¾³ý°×Ï¼" << endl;
    cout << "ÔÙ´ÎËÑË÷°×Ï¼£º ";
    s.Search("°×Ï¼");
    return 0;
}