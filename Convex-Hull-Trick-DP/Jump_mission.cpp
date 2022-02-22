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

inline int Int(){int x ; scanf("%d",&x) ; return x ;}
inline ll Long(){ll x ; scanf("%lld",&x) ; return x ;}

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

const int N          = (int)3e5 + 5 ;
const int maxN       = (int)1e6 + 6 ;
const ll  Mod        = (ll)1e9 + 7 ;
const int inf        = (int)2e9 ;
const ll  Inf        = (ll)1e18 ;
const int mod        = (int)1e9 + 7 ;

/*..........................................................*/
/*...Part - 05...*/

#define     debug(x)    cerr << #x << " = " << x << '\n' ;
#define     rep(i,b,e)  for(__typeof(e) i = (b) ; i != (e + 1) - 2 * ((b) > (e))  ; i += 1 - 2 * ((b) > (e)))
#define     Int         Int()
#define     Long        Long()
#define     all(x)      x.begin() , x.end()
#define     rall(x)     x.rbegin() , x.rend()
#define     sz(x)       (int)x.size()
#define     ff          first
#define     ss          second
#define     pb          push_back
#define     eb          emplace_back
#define     swap(a, b)  (((a) ^= (b)), ((b) ^= (a)), ((a) ^= (b)))
#define     mem(a)      memset(a , 0 ,sizeof a)
#define     memn(a)     memset(a , -1 ,sizeof a)
#define     filein      freopen("input.txt","r",stdin)
#define     fileout     freopen("output.txt","w",stdout)

inline int add(int a, int b){a += b ;return a >= mod ? a - mod : a ;}
inline int sub(int a, int b){a -= b ;return a < 0 ? a + mod : a ;}
inline int mul(int a, int b){return (ll)a * b % mod ;}

/*...Part - 06...*/
/*...... ! Code start from here ! ......*/

bool tp ;
struct Line{
	mutable ll m, c, p ;
	bool operator<(const Line& u)const{return tp ? p < u.p : m < u.m ;}
	bool operator<(ll u){return p < u ;}
} ;

struct DynamicCHT : multiset < Line > {
	ll div(ll a, ll b){
		return a / b - ((a ^ b) < 0 and (a % b)) ;
	}
	bool isect(iterator x, iterator y){
		if(y == end()){x->p = Inf ;return false ;}
		if(x->m == y->m)x->p = x->c >= y->c ? Inf : -Inf ;
		else x->p = div(x->c - y->c, y->m - x->m) ;
		return x->p >= y->p;
	}
	void add(ll x, ll y){
		auto c = insert({x, y, 0}), b = c++, a = b ;
		while(isect(b, c))c = erase(c) ;
		if(a != begin() and isect(--a, b))isect(a, b = erase(b)) ;
		while((b = a) != begin() and (--a)->p >= b->p){
			isect(a, erase(b)) ;
		}
	}
	ll query(ll x){
		assert(!empty()) ;
		tp = 1 ;
		auto u = *lower_bound({0, 0, x}) ;
		tp = 0 ;
		return u.m * x + u.c ;
	}
} ;

vector < DynamicCHT > T ;

void update(int i, int b, int e, int p, ll x, ll y){
	T[i].add(x, y) ;
	if(b == e)return ;
	int mid = (b + e) >> 1 ;
	if(p <= mid)update(i << 1, b, mid, p, x, y) ;
	else update(i << 1 | 1, mid + 1, e, p, x, y) ;
}

ll query(int i, int b, int e, int l, int r, ll x){
	if(b > r or e < l)return Inf ;
	if(b >= l and e <= r){
		if(!sz(T[i]))return Inf ;
		return -1LL * T[i].query(x) ;
	}
	int mid = (b + e) >> 1 ;
	return min(query(i << 1, b, mid, l, r, x), query(i << 1 | 1, mid + 1, e, l, r, x)) ;
}

int p[N] ;
ll a[N], h[N] ;

int main(){
    int test = 1 , tc = 0 ;
    while(test--){
        int n = Int ;
        T.resize((n << 2) + 5) ;
        for(int i = 1 ; i <= n ; ++i)p[i] = Int ;
        for(int i = 1 ; i <= n ; ++i)a[i] = Long ;
        for(int i = 1 ; i <= n ; ++i)h[i] = Long ;
        update(1, 1, n, 1, 2LL * h[1], -1LL * ((h[1] * h[1]) + a[1])) ;
    	ll res = a[1] ;
        for(int i = 2 ; i <= n ; ++i){
        	res = query(1, 1, n, 1, p[i] - 1, h[i]) + (h[i] * h[i]) + a[i] ;
        	update(1, 1, n, p[i], 2LL * h[i], -(res + (h[i] * h[i]))) ;
        }
        cout << res << '\n' ;
    }
    return 0 ;
}

/*...Always look at the part - 04...*/
/*...............END................*/



