#include "StudentHash.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cmath>

StuInf::StuInf(){
    age = 0;
    gender = "x";
    name = "xxxx";
    stuNum = "00000000000";
    phoneNum = "00000000000";
}

StuInf::StuInf(string na, string num, string gen, int ag, string pho):
name(na), stuNum(num), gender(gen), age(ag), phoneNum(pho){ }

StuHash::StuHash(){
    hashFunTimes = 0;
    StuInf buf;
    for(int i = 0; i < maxNum; i ++){
        stuTable[i] = buf;
    }
}

int StuHash::StuHashFun(string name, int times){
    unsigned int hash = 1;
    for(int i = 0; i < name.size(); i ++){
        hash += (i + 3) * (1 + 2 * i) * (unsigned char)(name.at(i));
    }
    unsigned int w = 1024, m = w / maxNum;
    unsigned int A1 = 723, A2 = 599;    // A1 = 1011010011 A2 = 1001010111
    unsigned int hash1 = ((A1 * hash) % w) / m,
        hash2 = ((A2 * hash) % w) / m;
    hash = (times * hash1 +  hash2) % maxNum;
    hashFunTimes += 1;
    return hash;
}

StuInf StuHash::Search(string name){
    int buf;
    for(int i = 0; i < maxNum; i++){
        buf = StuHashFun(name, i);
        if(stuTable[buf].name == name) return stuTable[buf];
        if(stuTable[buf].age == 0){
            cout << "Not Found!" << endl;
            return stuTable[buf];
        }
    }
     return stuTable[buf];
}

void StuHash::Insert(string name, StuInf stu){
    for(int i = 0; i < maxNum; i ++){
        int buf = StuHashFun(name, i);
        if(stuTable[buf].gender == "x"){
            stuTable[buf] = stu;
            break;
        }

    }
}
void StuHash::Delete(string name){
    for(int i = 0; i < maxNum; i++){
        int buf = StuHashFun(name, i);
        if(stuTable[buf].name == name){
            StuInf inf;
            inf.age = -1;
            stuTable[buf] = inf;
            break;
        }
        if(stuTable[buf].age == 0){
            cout << "Not Found!" << endl;
            break;
        }
    }
}
void StuHash::ReadinCSV(string name){
    ifstream inFile(name, ios::in);
    if(!inFile){
        cout << "Fail!" << endl;
        return;
    }
    string line;
    getline(inFile, line);
    while(getline(inFile, line)){
        string temp;
        StuInf buf;
        istringstream sin(line);
        getline(sin, temp, ',');
        buf.name = temp; 
        getline(sin, temp, ',');
        buf.stuNum = temp;
        getline(sin, temp, ',');
        buf.gender = temp;
        getline(sin, temp, ',');
        buf.age = atoi(temp.c_str());
        getline(sin, temp, ',');
        buf.phoneNum = temp; 
        Insert(buf.name, buf);
    }
}