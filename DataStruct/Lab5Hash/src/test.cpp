#include "StudentHash.h"
#include <iostream>

using namespace std;

int main(){
    StuHash s;
    s.ReadinCSV("data.csv");
    cout << "ƽ������ʱ��:" << s.hashFunTimes / 149.0 << endl;
    cout << "����ʾ����" << endl;
    StuInf a = s.Search("�춬÷");
    cout << a.name << ":" << a.stuNum << a.gender << a.age << "��" << a.phoneNum << endl;
    a = s.Search("��ϼ");
    cout << a.name << ":" << a.stuNum << a.gender << a.age << "��" << a.phoneNum << endl;
    cout << "ɾ��ʾ����" << endl;
    s.Delete("��ϼ"); 
    cout << "��ɾ����ϼ" << endl;
    cout << "�ٴ�������ϼ�� ";
    s.Search("��ϼ");
    return 0;
}