/*...Part - 01...*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <deque>
#include <iterator>
#include <bitset>
#include <assert.h>
#include <new>
#include <sstream>
//#include <bits/stdc++.h>
using namespace std ;

/*...Part - 02...*/

typedef long long               ll ;
typedef long double             ld ;
typedef unsigned long long      ull ;
typedef pair<int,int>           pii ;
typedef pair<ll,ll>             pll ;
typedef vector<int>             vi ;
typedef vector<ll>              vll ;
typedef vector<vector<int>>     vvi ;

int Int(){int x ; scanf("%d",&x) ; return x ;}
ll Long(){ll x ; scanf("%lld",&x) ; return x ;}

/*...Part - 03...*/
/*....Debugger....*/

#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) {cout << endl ;}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cerr << *it << " = " << a << ' ' ;
    err(++it, args...);
}

/*...Part - 04...*/
/*...Needed to change according to problem requirements...*/

const int N          = (int)2e5 + 5 ;
const int maxN       = (int)1e6 + 6 ;
const ll  Mod        = (ll)1e9 + 7 ;
const int inf        = (int)2e9 ;
const ll  Inf        = (ll)1e18 ;

/*..........................................................*/
/*...Part - 05...*/

#define     debug(x)    cerr << #x << " = " << x << '\n' ;
#define     rep(i,b,e)  for(__typeof(e) i = (b) ; i != (e + 1) - 2 * ((b) > (e))  ; i += 1 - 2 * ((b) > (e)))
#define     Int         Int()
#define     Long        Long()
#define     all(x)      x.begin() , x.end()
#define     sz(x)       (int)x.size()
#define     ff          first
#define     ss          second
#define     pb          push_back
#define     eb          emplace_back
#define     mem(a)      memset(a , 0 ,sizeof a)
#define     memn(a)     memset(a , -1 ,sizeof a)

/*...Part - 06...*/
/*...... ! Code start from here ! ......*/

int mod ;

struct Matrix{
	vector < vector < int > > mat ;
	int row, col ;
	Matrix(vector < vector < int > > values): mat(values), row((int)values.size()), col((int)values[0].size()){}
	
	static Matrix Identity_matrix(int n){
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
					res[i][j] += (mat[i][k] * other.mat[k][j]) % mod ;
					res[i][j] %= mod ;
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
	Matrix res = Matrix::Identity_matrix(m.row) ;
	while(p){
		if(p & 1)res = res * m ;
		m = m * m ;
		p >>= 1 ;
	}
	return res ;
}

int main(){
    int test = Int , tc = 0 ;
    while(test--){
    	vi a(3), b(3), f(3), g(3) ;
    	for(int i = 0 ; i < 3 ; ++i)a[i] = Int ;
        for(int i = 0 ; i < 3 ; ++i)b[i] = Int ;
        for(int i = 0 ; i < 3 ; ++i)f[i] = Int ;
        for(int i = 0 ; i < 3 ; ++i)g[i] = Int ;
        vector < vector < int > > v(6, vector < int > (6, 0)) ;
        vector < vector < int > > tmp(6, vector < int > (1, 0)) ;
    	v[0][0] = a[0], v[0][1] = a[1], v[0][5] = a[2] ;
    	v[3][2] = b[2], v[3][3] = b[0], v[3][4] = b[1] ;
    	v[1][0] = v[2][1] = v[4][3] = v[5][4] = 1 ;
    	for(int i = 0 ; i < 3 ; ++i)tmp[i][0] = f[2 - i] ;
    	for(int i = 3 ; i < 6 ; ++i)tmp[i][0] = g[5 - i] ;
    	Matrix M(v), H(tmp) ;
    	mod = Int ;
        int q = Int ;
        printf("Case %d:\n",++tc);
        while(q--){
        	int n = Int ; 
        	if(n <= 2)printf("%d %d\n",f[n] % mod, g[n] % mod);
        	else{
        		Matrix res = modpow(M, n - 2) ;
        		res = res * H ;
        		int ff = (res.mat[0][0]) % mod ;
        		int gg = (res.mat[3][0]) % mod ;
        		printf("%d %d\n",ff % mod, gg % mod);
        	}
        }
    }
    return 0 ;
}

/*...Always look at the part - 04...*/
/*...............END................*/


