#include "Sort.h"

void InsertionSort(int arr[], int lenth, int start){
    for(int i = start + 1; i < lenth; i ++){
        int buf = arr[i], j = i;
        while(buf < arr[j - 1] && j > 0){
            arr[j] = arr[j - 1];
            j --;
        }
        arr[j] = buf;
    }
}

void MergeSort(int arr[], int start, int end){
    static int buff[N];
    if(start >= end) return;
    int leftStart = start, leftEnd = (start + end) / 2;
    int rightStart = leftEnd + 1, rightEnd = end;
    MergeSort(arr, leftStart, leftEnd);
    MergeSort(arr, rightStart, rightEnd);
    int i = leftStart, j = rightStart, k = start;
    for(; i <= leftEnd && j <= rightEnd; k++){
        if(arr[i] < arr[j]){
            buff[k] = arr[i];
            i ++;
        }else{
            buff[k] = arr[j];
            j ++;
        }
    }
    int restHead = i > leftEnd ? j : i, restTail = i > leftEnd ? rightEnd : leftEnd;
    while(restHead <= restTail){
        buff[k] = arr[restHead];
        restHead ++; k++;
    }
    for(int i = start; i <= end; i ++){
        arr[i] = buff[i];
    }
}

void Merge_InsertionSort(int arr[], int start, int end, int K){
    static int buff[N];
    if(start >= end) return;
    int lenth = end - start + 1;
    if(lenth < K) InsertionSort(arr, lenth, start);
    int leftStart = start, leftEnd = (start + end) / 2;
    int rightStart = leftEnd + 1, rightEnd = end;
    Merge_InsertionSort(arr, leftStart, leftEnd, K);
    Merge_InsertionSort(arr, rightStart, rightEnd, K);
    int i = leftStart, j = rightStart, k = start;
    for(; i <= leftEnd && j <= rightEnd; k++){
        if(arr[i] < arr[j]){
            buff[k] = arr[i];
            i ++;
        }else{
            buff[k] = arr[j];
            j ++;
        }
    }
    int restHead = i > leftEnd ? j : i, restTail = i > leftEnd ? rightEnd : leftEnd;
    while(restHead <= restTail){
        buff[k] = arr[restHead];
        restHead ++; k++;
    }
    for(int i = start; i <= end; i ++){
        arr[i] = buff[i];
    }
}