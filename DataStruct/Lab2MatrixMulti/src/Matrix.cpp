#include "Matrix.h"
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>

Matrix::Matrix(int r, int c):row(r), col(c){
	if(col < 0) col = row;
    int *buf = new int[row * col];
	val = new int *[row];
	for(int i = 0; i < row; i++){
		val[i] = buf + i * col;
	}
	for(int i = 0; i < row; i ++){
		for(int j = 0; j < col; j ++){
			val[i][j] = 0;
		}
	}
}
Matrix::Matrix(const Matrix& A):row(A.col), col(A.row){
	int *buf = new int[row * col];
	val = new int *[row];
	for(int i = 0; i < row; i++){
		val[i] = buf + i * col;
	}
	for(int i = 0; i < row; i ++){
		for(int j = 0; j < col; j ++){
			val[i][j] = A.val[i][j];
		}
	}
}
Matrix::~Matrix(){
	if(val != NULL)
    delete [] val;
	val = NULL;
}
Matrix Matrix::operator+(const Matrix& A){
	Matrix temp(row, col);
	for(int i = 0; i < row; i ++){
		for(int j = 0; j < col; j++){
			temp.val[i][j] = val[i][j] + A.val[i][j];
		}
	}
	return temp;	
} 
Matrix Matrix::operator-(const Matrix& A){
	Matrix temp(row, col);
	for(int i = 0; i < row; i ++){
		for(int j = 0; j < col; j++){
			temp.val[i][j] = val[i][j] - A.val[i][j];
		}
	}
	return temp;	
} 

ostream& operator<<(ostream& out, Matrix& A){
	for(int i = 0; i < A.row; i ++){
		for(int j = 0; j < A.col; j++){
			out << setw(4) << A.val[i][j] << " ";
		}
		out << endl;
	}
	return out;
}
void Matrix::RandomAssign(int max){
	for(int i = 0; i < row; i ++){
		for(int j = 0; j < col; j++){
			val[i][j] = rand()%max;
		}
	}
}
void Matrix::CopyValue(const Matrix &A, int x, int y){
	for(int i = 0; i < row; i ++){
		for(int j = 0; j < col; j ++){
			val[i][j] = A.val[i + x][j + y];
		}
	}
}
void Matrix::AreaAssign(const Matrix &A, int x, int y){
	for(int i = 0; i < A.row; i ++){
		for(int j = 0; j < A.col; j ++){
			val[i + x][j + y] = A.val[i][j];
		}
	}
}
Matrix* Matrix::StrassenMultiplication(const Matrix& B){
	if(col != B.row){
        cout << "Wrong!" << endl;
        return NULL;
    }
	int size = row > col ? row : col, ss;
	Matrix *result = new Matrix(row, B.col);
	for(ss = 1; ss < size; ss *= 2){}
	size = ss;
	Matrix buf1(size), buf2(size);
	buf1.AreaAssign(*this, 0, 0);	buf2.AreaAssign(B, 0, 0);
	result->CopyValue(buf1.StrassenRecursion(buf2), 0, 0);
	return result;
}
Matrix Matrix::StrassenRecursion(const Matrix& B){
	if(row == 1){
		Matrix result(1);
		result.val[0][0] = val[0][0] * B.val[0][0];
		return result;
	}
	int s = row / 2;
	Matrix A11(s), A12(s), A21(s), A22(s), B11(s), B12(s), B21(s), B22(s);
	A11.CopyValue(*this, 0, 0);	A12.CopyValue(*this, 0, s);
	A21.CopyValue(*this, s, 0);	A22.CopyValue(*this, s, s);
	B11.CopyValue(B, 0, 0);	B12.CopyValue(B, 0, s);
	B21.CopyValue(B, s, 0);	B22.CopyValue(B, s, s);
	Matrix S1(B12 - B22), 
	S2(A11 + A12),	S3(A21 + A22),	S4(B21 - B11),
	S5(A11 + A22),	S6(B11 + B22), 	S7(A12 - A22), 
	S8(B21 + B22),	S9(A11 - A21),	S10(B11 + B12);	
	Matrix P1(A11.StrassenRecursion(S1)),
	P2(S2.StrassenRecursion(B22)),	P3(S3.StrassenRecursion(B11)),	
	P4(A22.StrassenRecursion(S4)),	P5(S5.StrassenRecursion(S6)),
	P6(S7.StrassenRecursion(S8)),	P7(S9.StrassenRecursion(S10));
	Matrix C11(P5 + P4 - P2 + P6),	C12(P1 + P2),	
		C21(P3 + P4),	C22(P5 + P1 - P3 - P7);
	Matrix result(row);
	result.AreaAssign(C11, 0, 0);
	result.AreaAssign(C12, 0, s);
	result.AreaAssign(C21, s, 0);
	result.AreaAssign(C22, s, s);
	return result;
}

Matrix* Matrix::Multiplication(const Matrix& B){
	Matrix *Result = new Matrix(row, B.col);
    if(col != B.row){
        cout << "Wrong!" << endl;
        return NULL;
    }
	for(int i = 0; i < row; i ++){
		for(int j = 0; j < B.col; j ++){
			for(int k = 0; k < col; k ++){
				Result->val[i][j] += val[i][k] * B.val[k][j];
			}
		}
	}
    return Result;
}