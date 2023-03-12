#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
using namespace std;

class Matrix{
    friend ostream& operator<<(ostream& out, Matrix& A);
private:
    int **val;
    int row;
    int col;
    void CopyValue(const Matrix &A, int x, int y);
    void AreaAssign(const Matrix &A, int x, int y);
    Matrix StrassenRecursion(const Matrix& B);
public:
    Matrix(int row, int col = -1);
    Matrix(const Matrix &A);
    ~Matrix();
    //...
    Matrix operator+(const Matrix& A);
    Matrix operator-(const Matrix& A);
    void RandomAssign(int max = 20);
    Matrix* StrassenMultiplication(const Matrix& B);
    Matrix* Multiplication(const Matrix& B);
};

#endif
