#ifndef D_ARY_HEAPS_H
#define D_ARY_HEAPS_H
using namespace std;

const int maxSize = 100;

class DAryHeap{
    const int d;
public:
    int val[maxSize];
    int end;
    DAryHeap(int dd);
    void BuildMaxHeap(int arr[], int size);
    int GetParent(int i);
    int GetChild(int i, int k);
    int GetHeight();
    void MaxHeapify(int i);
    void IncreaseKey(int i, int k);
    int ExtractMax();
    void Insert(int a);
};

void Exchange(int &a, int &b);
#endif