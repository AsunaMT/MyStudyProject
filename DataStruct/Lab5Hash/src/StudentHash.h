#ifndef STUDENTHASH_H
#define STUDENTHASH_H

#include <string>
using namespace std;

const int maxNum = 256;

class StuInf{
public:
    string name; 
    string stuNum;
    string gender;
    int age;
    string phoneNum;
    StuInf();
    StuInf(string na, string num, string gen, int ag, string pho);
};

class StuHash{
    StuInf stuTable[maxNum];
    int StuHashFun(string name, int times);
public:
    int hashFunTimes;
    StuHash();
    void ReadinCSV(string name);
    StuInf Search(string name);
    void Insert(string name, StuInf stu);
    void Delete(string name);
};

#endif