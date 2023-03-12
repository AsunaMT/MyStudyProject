#include <iostream>
#include "d_ary_heaps.h"
using namespace std;

int main(){
    int a[20] = {19,34,32,2,7,19,8,12,33,28,27,16,56,23,47,49,51,42,11,1};
    DAryHeap D(3);
    D.BuildMaxHeap(a, 20);
    cout << D.val[0] << endl;
    int m = D.ExtractMax();
    cout << "Height: " << D.GetHeight() << "\n" <<m << endl;
    D.Insert(66);
    cout << D.ExtractMax() << endl;
    return 0;
}