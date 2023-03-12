#include "d_ary_heaps.h"
#include <cmath>
#include <iostream>

DAryHeap::DAryHeap(int dd):d(dd){}

void DAryHeap::BuildMaxHeap(int arr[], int size){
    end = size;
    for(int i = 0; i < end ; i ++){
        val[i] = arr[i];
    }
    for(int i = end; i > 0; i --){
        Exchange(val[0], val[i]);
        MaxHeapify(0);
    }
}

int DAryHeap::GetParent(int i){
    if(i == 0) return -1;
    return (int)((i - 1) / d);
}
int DAryHeap::GetChild(int i, int k){
    return d * i + k;
}
int DAryHeap::GetHeight(){
    return (int)(log(end) / log(d)) + 1;
}
void DAryHeap::MaxHeapify(int i){
    int largest = i;
    for(int k = GetChild(i , 1); k <= GetChild(i, d) && k <= end; k ++){
        if(val[largest] < val[k])   largest = k;
    }
    if(largest == i) return;
    Exchange(val[i], val[largest]);
    MaxHeapify(largest);
}
void DAryHeap::IncreaseKey(int i, int k){
    val[i] = k > val[i] ? k : val[i];
    while(i > 0 && val[i] > val[GetParent(i)]){
        Exchange(val[i], val[GetParent(i)]);
        i = GetParent(i); 
    }
}
int DAryHeap::ExtractMax(){
    Exchange(val[0], val[end]);
    end --;
    MaxHeapify(0);
    return val[end + 1];
}
void DAryHeap::Insert(int a){
    end ++;
    val[end] = INT_MIN;
    IncreaseKey(end, a);
}

void Exchange(int &a, int &b){
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}