#include <bits/stdc++.h>
using namespace std ;
const static long long Mod = (long long)1e9 + 7 ;

struct Matrix{
	vector < vector < int > > mat ;
	int row, col ;
	Matrix(vector < vector < int > > values): mat(values), row((int)values.size()), col((int)values[0].size()){}
	
	static Matrix Idntity_matrix(int n){
		vector < vector < int > > tmp(n, vector < int >(n ,0)) ;
		for(int i = 0 ; i < n ; ++i)
			tmp[i][i] = 1;
		return tmp ;
	}

	Matrix operator*(const Matrix& other) const {
		int n = row, m = other.col ;
		vector < vector < int > > res(n, vector < int > (m, 0)) ;
		for(int i = 0 ; i < n ; ++i){
			for(int j = 0 ; j < m ; ++j){
				for(int k = 0;  k < col ; ++k){
					res[i][j] += (mat[i][k] * other.mat[k][j]) % Mod ;
					res[i][j] %= Mod ;
				}
			}
		}
		return Matrix(res) ;
	}

	inline bool is_square() const{
		return row == col ;
	}
} ;

Matrix modpow(Matrix m, int p){
	Matrix res = Matrix::Idntity_matrix(m.row) ;
	while(p){
		if(p & 1)res = res * m ;
		m = m * m ;
		p >>= 1 ;
	}
	return res ;
}

int main(){
	Matrix M({{1, 1}, {1, 0}}) ; // For Fibonacci
	return 0;
}