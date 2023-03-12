#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Sort.h"
using namespace std;

int main(){
    srand(time(NULL));
    int arr[3][20];
    for(int i = 0; i < 3; i ++){
        cout << "*" ;
        for(int j = 0; j < 20; j ++){
            arr[i][j] = rand()%100;
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    InsertionSort(arr[0], 20);
    cout << "InsertionSort: ";
    for(int i = 0; i < 20 ; i++){
        cout << arr[0][i] << " ";
    }
    cout << endl;
    MergeSort(arr[1], 0, 19);
    cout << "MergeSort: ";
    for(int i = 0; i < 20 ; i++){
        cout << arr[1][i] << " ";
    }
    cout << endl;
    Merge_InsertionSort(arr[2], 0, 19);
    cout << "Merge_InsertionSort: ";
    for(int i = 0; i < 20 ; i++){
        cout << arr[2][i] << " ";
    }
    cout << endl;
    return 0;
}
