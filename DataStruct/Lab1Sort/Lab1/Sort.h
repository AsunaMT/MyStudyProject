#ifndef SORT_H
#define SORT_H

const int bound = 24;
const int N = 10000;

void InsertionSort(int arr[], int lenth,int start = 0);

void MergeSort(int arr[], int start, int end);

void Merge_InsertionSort(int arr[], int start, int end, int K = bound); 

#endif