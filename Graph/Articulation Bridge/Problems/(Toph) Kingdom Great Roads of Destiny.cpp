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

/* Input Section */

template <typename T> inline void Int(T &a){
    bool minus = false; a = 0; char ch = getchar();
    while (true) { if (ch == '-' or (ch >= '0' && ch <= '9')) break; ch = getchar(); }
    if (ch == '-') minus = true; else a = ch - '0';
    while (true) { ch = getchar(); if (ch < '0' || ch > '9') break; a = a * 10 + (ch - '0'); }
    if(minus)a *= -1 ;
}
template < typename T > inline void Int(T &a, T &b){Int(a), Int(b) ;}
template < typename T > inline void Int(T &a, T &b, T&c){Int(a, b), Int(c) ;}
template < typename T > inline void Int(T &a, T &b, T&c, T& d){Int(a, b), Int(c, d) ;}


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
const int mod        = (int)1e9 + 7 ;

/*..........................................................*/
/*...Part - 05...*/

#define     debug(x)    cerr << #x << " = " << x << '\n' ;
#define     rep(i,b,e)  for(__typeof(e) i = (b) ; i != (e + 1) - 2 * ((b) > (e))  ; i += 1 - 2 * ((b) > (e)))
#define     all(x)      x.begin() , x.end()
#define     rall(x)     x.rbegin() , x.rend()
#define     sz(x)       (int)x.size()
#define     ff          first
#define     ss          second
#define     pb          push_back
#define     eb          emplace_back
#define     mem(a)      memset(a , 0 ,sizeof a)
#define     memn(a)     memset(a , -1 ,sizeof a)
#define     Fread      freopen("input.txt","r",stdin)
#define     Fwrite     freopen("output.txt","w",stdout)

inline int add(int a, int b, int mod){a += b ;return a >= mod ? a - mod : a ;}
inline int sub(int a, int b, int mod){a -= b ;return a < 0 ? a + mod : a ;}
inline int mul(int a, int b, int mod){return (ll)a * b % mod ;}

/*...Part - 06...*/
/*...... ! Code start from here ! ......*/

int low[N], in[N], tm, P[N], Rank[N], comp[N], par[N][20], dep[N] ;
vector < pii > setu ;
vvi g ;

void init(){
	setu.clear() ;
	g.clear() ;
	tm = 0 ;
	mem(low) ;
	mem(in) ;
}

void build(){
	for(int i = 0 ; i < N ; ++i)
		P[i] = i, Rank[i] = 1 ;
}

int Find(int x){
	return P[x] = P[x] == x ? x : Find(P[x]) ;
}

void merge(int x, int y){
	x = Find(x), y = Find(y) ;
	if(x == y)return ;
	if(Rank[x] < Rank[y])swap(x, y) ;
	P[y] = x, Rank[x] += Rank[y] ;
}

void bridge(int s, int p = 0){
	low[s] = in[s] = ++tm ;
	for(int i : g[s]){
		if(i == p)continue ;
		if(in[i])low[s] = min(low[s], in[i]) ;
		else{
			bridge(i, s) ;
			low[s] = min(low[s], low[i]) ;
			if(low[i] > in[s])setu.pb(make_pair(i, s)) ;
			else merge(i, s) ;
		}
	}
}

void dfs(int s, int p = 0){
	par[s][0] = p ;
	dep[s] = 1 + dep[p] ;
	for(int i = 1 ; i < 20 ; ++i)
		par[s][i] = par[par[s][i - 1]][i - 1] ;
	for(int i : g[s]){
		if(i - p)dfs(i, s) ;
	}
}

int LCA(int a, int b){
	if(dep[a] < dep[b])swap(a, b) ;
	int d = dep[a] - dep[b] ;
	for(int i = 19 ; i >= 0 ; --i)
		if(d & (1 << i))a = par[a][i] ;
	if(a == b)return a ;
	for(int i = 19 ; i >= 0 ; --i)
		if(par[a][i] != par[b][i])
			a = par[a][i], b = par[b][i] ;
	return par[a][0] ;
}

int main(){
    int test = 1 , tc = 0 ;
    Int(test) ;
    while(test--){
    	init() ;
    	int n, m ; Int(n, m) ;
    	g.resize(n + 1) ;
    	for(int i = 1 ; i <= m ; ++i){
    		int x, y ; Int(x, y) ;
    		g[x].pb(y) ;
    		g[y].pb(x) ;
    	}
    	build() ;
    	bridge(1) ;
    	vi cnt(n + 1, 0) ;
    	int id = 0 ;
    	for(int i = 1 ; i <= n ; ++i){
    		comp[i] = Find(i) ;
    		if(!cnt[comp[i]])cnt[comp[i]] = ++id ;
    		//error(comp[i])
    	}
    	//error(id)
    	g.clear(), g.resize(id + 1) ;
    	for(pii i : setu){
    		int x = cnt[comp[i.ff]], y = cnt[comp[i.ss]] ;
    		g[x].pb(y) ;
    		g[y].pb(x) ;
    	}
    	dfs(1) ;
    	int q ; Int(q) ;
    	printf("Case %d:\n",++tc);
    	while(q--){
    		int x, y ; Int(x, y) ;
    		x = cnt[comp[x]], y = cnt[comp[y]] ;
    		int res = 0 ;
    		//error(x, y, dep[x], dep[y])
    		if(x != y)res = dep[x] + dep[y] - 2 * dep[LCA(x, y)] ;
    		printf("%d\n",res);
    	}
    }
    return 0 ;
}

/*...Always look at the part - 04...*/
/*...............END................*/

