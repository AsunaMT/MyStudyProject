#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "Sort.h"
using namespace std;

const int lenthA = 8000;
const int nums = 60;

int SeekForOneK();
int VerifyK(int K);

int main(){
    int K = 0;
    for(int i = 0; i < nums; i ++){
        K += SeekForOneK();
    }
    K = K / nums;
    cout << "K = " << K << endl;
    K = VerifyK(K);
    cout << "K = " << K << endl;
    return 0;
}


int SeekForOneK(){
    double c1, c2;
    srand(time(NULL));
    int arr[nums][lenthA];
    for(int i = 0; i < nums; i ++){
        for(int j = 0; j < lenthA; j ++){
            arr[i][j] = rand()%10000;
        }
    }
    clock_t start = clock();
    for(int i = 0; i < nums; i ++){
            MergeSort(arr[i], 0, lenthA - 1);
    }
    clock_t end = clock(); 
    int result = end - start;
    c1 = 100 * result/log10(lenthA);
    for(int i = 0; i < nums; i ++){
        for(int j = 0; j < lenthA; j ++){
            arr[i][j] = rand()%10000;
        }
    }
    start = clock();
    for(int i = 0; i < nums; i ++){
        InsertionSort(arr[i], lenthA);
    }
    end = clock();
    result = end - start;       
    c2 = 100 * result / lenthA;
    double buf = c2 / c1;
    cout << "c2/c1 = " << buf << endl;
    cout << c1 / (c2 * log(10)) << endl;
    return c1 / (c2 * log(10)) ;
}

int VerifyK(int K){
    int trueK, minTime = 999999;
    for(int val = K * 0.7; val < K * 1.3; val ++){
        int result = 0;
        for(int i = 0; i < 300; i ++){      
            int arr[nums][lenthA];
            for(int i = 0; i < nums; i ++){
                for(int j = 0; j < lenthA; j ++){
                    arr[i][j] = rand()%10000;
                }
            }
            clock_t start = clock();
            for(int i = 0; i < nums; i ++){
                Merge_InsertionSort(arr[i], 0, lenthA - 1, val);
            }
            clock_t end = clock();
            //cout << end - start << "   "; 
            result += end - start;
        }
        cout << result / 150 << "ms " << "K = " << val <<  endl;
        if(result < minTime){
            minTime = result;
            trueK = val;
        }
    }
    return trueK;
}