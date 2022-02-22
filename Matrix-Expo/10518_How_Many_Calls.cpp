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
const ll  Mod        = (ll)1e9 + 9 ;
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
	ll mat[3][3] ;
	matrix(){
		mem(mat) ;
	}
};

matrix mul(matrix a, matrix b, ll mod){
	matrix ans ;
	for(int i = 0 ; i < 3 ; ++i){
		for(int j = 0 ; j < 3 ; ++j){
			for(int k = 0 ; k < 3 ; ++k){
				ans.mat[i][j] = (ans.mat[i][j] + (a.mat[i][k] * b.mat[k][j])) % mod ;
			}
		}
	}
	return ans ;
}

matrix modpow(matrix b, ll p, ll mod){
	matrix res ;
	for(int i = 0 ; i < 3 ; ++i){
		for(int j = 0 ; j < 3 ; ++j){
			res.mat[i][j] = i == j ;
		}
	}
	while(p){
		if(p & 1)res = mul(res, b, mod) ;
		b = mul(b, b, mod) ;
		p >>= 1LL ;
	}
	return res ;
}

int main(){
	// freopen("input.txt","r",stdin);
 //    freopen("output.txt","w",stdout);
    int test = 1 , tc = 0 ;
    ll n, b;
    while(cin >> n >> b and (n or b)){
        if(n <= 1)printf("Case %d: %lld %lld %lld\n",++tc, n, b, 1LL % b);
        else{
        	matrix res ;
        	res.mat[0][0] = res.mat[0][1] = res.mat[0][2] = res.mat[1][0] = res.mat[2][2] = 1 ;
        	res = modpow(res, n - 1, b) ;
        	ll ans = (res.mat[0][0] + res.mat[0][1] + res.mat[0][2]) % b ;
        	printf("Case %d: %lld %lld %lld\n",++tc, n, b, ans);
        }
    }
    return 0 ;
}

/*...Always look at the part - 04...*/
/*...............END................*/


