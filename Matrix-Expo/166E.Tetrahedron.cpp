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

struct matrix{
	ll mat[4][4] ;
} ;

matrix multiply(matrix a, matrix b){
	matrix ans ;
	int i, j, k;
	for(i = 0 ; i < 4 ; ++i){
		for(j = 0 ; j < 4 ; ++j){
			for(ans.mat[i][j] = k = 0 ; k < 4 ; ++k){
				ans.mat[i][j] += (a.mat[i][k] * b.mat[k][j]) % Mod ;
				if(ans.mat[i][j] >= Mod)ans.mat[i][j] %= Mod ;
			}
		}
	}
	return ans ;
}

matrix matpow(matrix b, int p){
	matrix ans ;
	for(int i = 0 ; i < 4 ; ++i){
		for(int j = 0 ; j < 4 ; ++j){
			ans.mat[i][j] = (i == j) ;
		}
	}
	while(p > 0){
		if(p & 1)ans = multiply(ans, b) ;
		b = multiply(b, b) ;
		p >>= 1 ;
	}

	return ans ;
}

int main(){
    int n = Int ;
    matrix res ;
    for(int i = 0 ; i < 4 ; ++i)
    	for(int j = 0 ; j < 4 ; ++j)
    		res.mat[i][j] = i != j ;
    res = matpow(res, n) ;
    printf("%lld\n",res.mat[3][3] % Mod);
    return 0 ;
}

/*...Always look at the part - 04...*/
/*...............END................*/


