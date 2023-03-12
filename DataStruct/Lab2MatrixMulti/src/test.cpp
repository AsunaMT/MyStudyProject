#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include "Matrix.h"
using namespace std;

int main(int argc, char const *argv[]){
	for(int k = 128; k < 1024; k *= 2){
		const int size = k;
		Matrix A(size),B(size);
		Matrix *c = new Matrix(size);
		Matrix *d = new Matrix(size);
		A.RandomAssign(10);	B.RandomAssign(10);
		cout << "n = " << size << endl;
		clock_t start = clock();
		c = A.StrassenMultiplication(B);
		clock_t middle = clock();
		int time1 = middle - start;
		cout << "StrassenTime: " << time1 << "ms" << endl;
		d = A.Multiplication(B);
		clock_t end = clock();
		int time2 = end - middle;
		cout << "OrdinaryTime: " << time2 << "ms" << endl;
		cout << "StrassenTime/nlog27 = " << 1000.0*((double)time1) / pow(size, log(7)/log(2)) << endl;
		cout << "OrdinaryTime/n3 = " << 1000.0*((double)time2) / pow(size, 3) << endl;
	}
    return 0;
}