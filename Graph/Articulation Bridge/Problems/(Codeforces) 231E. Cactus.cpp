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
typedef pair<int, int>           pii ;
typedef pair<ll, ll>             pll ;
typedef vector<int>             vi ;
typedef vector<ll>              vll ;
typedef vector<vector<int>>     vvi ;

int Int() {int x ; scanf("%d", &x) ; return x ;}
ll Long() {ll x ; scanf("%lld", &x) ; return x ;}

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

const int N          = (int)1e5 + 5 ;
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


vvi g ;
int comp[N], tm, ans[N], par[N][18], dep[N], team[N], Rank[N], in[N], low[N];
ll res[N][18] ;

vector < pii > brg ;

void Set() {
	for (int i = 0 ; i < N ; ++i)
		team[i] = i , Rank[i] = 1 ;
}

int Find(int s) {
	return s == team[s] ? s : Find(team[s]) ;
}

void merge(int u, int v) {
	u = Find(u), v = Find(v) ;
	team[u] = v ;
	Rank[v] += Rank[u] ;
}

void bridge(int s, int p = 0) {
	low[s] = in[s] = ++tm ;
	for (int i : g[s]) {
		if (i == p)continue ;
		if (in[i])low[s] = min(low[s], in[i]) ;
		else {
			bridge(i, s) ;
			low[s] = min(low[s], low[i]) ;
			if (low[i] > in[s]) {
				brg.pb({s, i}) ;
			}
			else {
				merge(s, i) ;
			}
		}
	}
}

void dfs1(int s, int p = 0) {
	par[s][0] = p ;
	dep[s] = 1 + dep[p] ;
	res[s][0] = ans[p] ;
	for (int i = 1 ; i < 17 ; ++i) {
		par[s][i] = par[par[s][i - 1]][i - 1] ;
		res[s][i] = (res[s][i - 1] * res[par[s][i - 1]][i - 1]) % Mod ;
	}
	for (int i : g[s]) {
		if (i - p)dfs1(i, s) ;
	}
}

int LCA(int a, int b) {
	if (dep[a] < dep[b])swap(a, b) ;
	int d = dep[a] - dep[b] ;
	for (int i = 16 ; i >= 0 ; --i) {
		if (d & (1 << i))a = par[a][i] ;
	}
	if (a == b)return a;
	for (int i = 16 ; i >= 0 ; --i) {
		if (par[a][i] != par[b][i])
			a = par[a][i], b = par[b][i] ;
	}
	return par[a][0] ;
}

ll lift(int d, int a) {
	//error(d, a)
	if (!d)return 1LL ;
	ll cnt = ans[a] ;
	for (int i = 16 ; i >= 0 ; --i) {
		if (d & (1 << i)) {
			cnt = (cnt * res[a][i]) % Mod ;
			a = par[a][i] ;
		}
	}
	//error(d, a, cnt)
	return cnt ;
}



int main() {
	int test = 1 , tc = 0 ;
	while (test--) {
		int n = Int, m = Int ;
		g.resize(n + 1) ;
		for (int i = 1 ; i <= m ; ++i) {
			int x = Int, y = Int ;
			g[x].pb(y) ;
			g[y].pb(x) ;
		}
		Set() ;
		bridge(1) ;
		set < int > st ;
		vi ID(n + 1, 0) ;
		int cc = 0 ;
		for (int i = 1 ; i <= n ; ++i) {
			comp[i] = Find(i) ;
			if (!st.count(comp[i])) {
				ID[comp[i]] = ++cc ;
				st.insert(comp[i]) ;
				ans[ID[comp[i]]] = Rank[comp[i]] > 1 ? 2 : 1 ;
			}
		}
		n = cc ;
		g.clear() ;
		g.resize(n + 1);
		for (pii i : brg) {
			g[ID[comp[i.ff]]].pb(ID[comp[i.ss]]) ;
			g[ID[comp[i.ss]]].pb(ID[comp[i.ff]]) ;
		}
		dfs1(1) ;
		int q = Int ;
		while (q--) {
			int a = Int, b = Int ;
			a = ID[comp[a]], b = ID[comp[b]] ;
			if (a == b) {
				printf("%d\n", ans[a]);
				continue ;
			}
			int lca = LCA(a, b) ;
			if (dep[a] < dep[b])swap(a, b) ;
			int left = dep[a] - dep[lca], rgt = max(dep[b] - dep[lca] - 1, 0);
			// error(left, rgt, lca, a, b, dep[a], dep[b], dep[lca])
			// error(res[a][0], res[b][0], ans[a], ans[b])
			ll k = (lift(left, a) * lift(rgt, b)) % Mod ;
			if (rgt == 0 and b != lca)k = (k * ans[b]) % Mod ;
			printf("%lld\n", k % Mod);
		}
	}
	return 0 ;
}

/*...Always look at the part - 04...*/
/*...............END................*/


