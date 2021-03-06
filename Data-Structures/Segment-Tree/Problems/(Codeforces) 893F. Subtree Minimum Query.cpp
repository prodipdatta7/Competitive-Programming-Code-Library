/**
 *  “Experience is the name everyone gives to their mistakes.” – Oscar Wilde
 *
 *  author  :   prodipdatta7
 *  created :   Monday 08-June, 2020  10:19:04 PM
**/

//#include <bits/stdc++.h>
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
#include <time.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx,avx2,fma")
// #pragma GCC optimize("unroll-loops")

using namespace std ;
using namespace __gnu_pbds ;

#define     ll          long long
#define     ld          long double
#define     ull         unsigned long long
#define     pii         pair<int,int>
#define     pll         pair<ll,ll>
#define     vi          vector<int>
#define     vll         vector<ll>
#define     vvi         vector<vector<int>>
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
#define     fread       freopen("input.txt","r",stdin)
#define     fwrite      freopen("output.txt","w",stdout)
#define     TN          typename
#define     FastIO      ios_base::sync_with_stdio(false) ; cin.tie(NULL) ; cout.tie(NULL) ;

typedef tree <int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update > ordered_set;
typedef tree <int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update > ordered_multiset;

/*
Note :  There is a problem with erase() function in ordered_multiset (for less_equal<int> tag).
        lower_bound() works as upper_bound() and vice-versa.
        Be careful to use.
        i) find_by_order(k) : kth smallest element counting from 0 .
        ii) order_of_key(k) : number of elements strictly smaller than k.
*/

/*###############-> Input Section <-###############*/

template <TN T> inline void Int(T &a) {
	bool minus = false; a = 0; char ch = getchar();
	while (true) { if (ch == '-' or (ch >= '0' && ch <= '9')) break; ch = getchar(); }
	if (ch == '-') minus = true; else a = ch - '0';
	while (true) { ch = getchar(); if (ch < '0' || ch > '9') break; a = a * 10 + (ch - '0'); }
	if (minus)a *= -1 ;
}
template < TN T, TN T1 > inline void Int(T &a, T1 &b) {Int(a), Int(b) ;}
template < TN T, TN T1, TN T2 > inline void Int(T &a, T1 &b, T2 &c) {Int(a, b), Int(c) ;}
template < TN T, TN T1, TN T2, TN T3 > inline void Int(T &a, T1 &b, T2 &c, T3 &d) {Int(a, b), Int(c, d) ;}
template < TN T, TN T1, TN T2, TN T3, TN T4> inline void Int(T &a, T1 &b, T2 &c, T3 &d, T4 &e) {Int(a, b), Int(c, d, e) ;}

/*###############-> Debugger <-###############*/

#ifndef ONLINE_JUDGE
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) {cout << endl ;}
template<TN T, TN... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << *it << " = " << a << ' ' ;
	err(++it, args...);
}
#else
#define error(args...)
#endif

template<class ValueType>
bool unstable_remove(
    typename std::vector<ValueType>& container,
    typename std::vector<ValueType>::iterator it
) {
	auto lastEl = container.end() - 1;
	if (it != lastEl) {
		*it = std::move(*lastEl);
	}
	container.pop_back();
}

/******************************************
#Rows are numbered from top to bottom.
#Columns are numbered from left to right.
Moves : L, U, R, D, LU, RU, RD, LD.
******************************************/
int dx[8] = {0, -1, 0, 1, -1, -1, 1, 1} ;
int dy[8] = { -1, 0, 1, 0, -1, 1, 1, -1} ;

/*###############-> Constraints <-###############*/

const int N          = (int)2e5 + 5 ;
const int maxN       = (int)1e6 + 6 ;
const ll  Mod        = (ll)1e9 + 7 ;
const int inf        = (int)2e9 ;
const ll  Inf        = (ll)1e18 ;
const int mod        = (int)1e9 + 7 ;
const double EPS     = (double)1e-9 ;


inline int add(int a, int b, int mod) {a += b ; return a >= mod ? a - mod : a ;}
inline int sub(int a, int b, int mod) {a -= b ; return a < 0 ? a + mod : a ;}
inline int mul(int a, int b, int mod) {return (ll)a * b % mod ;}

/*...... ! Code starts from here ! ......*/

int tin[N], dep[N], subSize[N], c[N], t ;
vvi g ;
vector < pii > v, T[N << 2] ;

void dfs(int s, int p) {
	dep[s] = 1 + dep[p] ;
	subSize[s] = 1 ;
	tin[s] = ++t ;
	v[t] = make_pair(dep[s], c[s]) ;
	for (int i : g[s]) {
		if (i == p)continue ;
		dfs(i, s) ;
		subSize[s] += subSize[i] ;
	}

}

void build(int i, int b, int e) {
	if (b == e) {
		T[i].push_back(v[b]) ;
		return ;
	}
	int mid = b + e >> 1 ;
	build(i << 1, b, mid) ;
	build(i << 1 | 1, mid + 1, e) ;
	merge(all(T[i << 1]), all(T[i << 1 | 1]), back_inserter(T[i])) ;
	for (int j = 1 ; j < sz(T[i]) ; ++j) {
		if (T[i][j].ss > T[i][j - 1].ss)T[i][j].ss = T[i][j - 1].ss ;
	}
	// for(int j = 0 ; j < sz(T[i]) ; ++j)
	// 	error(i, T[i][j].ff, T[i][j].ss)
}

int query(int i, int b, int e, int l, int r, int d) {
	if (e < l or b > r)return inf ;
	if (l <= b and e <= r) {
		int lf = 0, rg = sz(T[i]) - 1, res = inf ;
		while (lf <= rg) {
			int m = lf + rg >> 1 ;
			if (T[i][m].ff <= d) {
				res = T[i][m].ss ;
				lf = m + 1 ;
			}
			else rg = m - 1 ;
		}
		return res ;
	}
	int mid = b + e >> 1 ;
	return min(query(i << 1, b, mid, l, r, d), query(i << 1 | 1, mid + 1, e, l, r, d)) ;
}

void solve() {
	int n, r; Int(n, r) ;
	for (int i = 1 ; i <= n ; ++i)
		Int(c[i]) ;
	g.resize(n + 1) ;
	for (int i = 1 ; i < n ; ++i) {
		int x, y ; Int(x, y) ;
		g[x].push_back(y) ;
		g[y].push_back(x) ;
	}
	v.resize(n + 1) ;
	dfs(r, 0) ;
	// for(int i = 1 ; i <= n ; ++i){
	// 	error(i, v[i].ff, v[i].ss)
	// }
	build(1, 1, n) ;
	int q ; Int(q) ;
	int last = 0 ;
	while (q--) {
		int x, k ; Int(x, k) ;
		x = ((x + last) % n) + 1, k = ((k + last) % n) ;
		//error(x, k)
		int l = tin[x], r = l + subSize[x] - 1 ;
		//error(l, r, k)
		last = query(1, 1, n, l, r, dep[x] + k) ;
		printf("%d\n", last);
	}
}

int main() {
#ifndef ONLINE_JUDGE
	clock_t tStart = clock();
	//freopen("input.txt", "r", stdin) ;
	//freopen("output.txt", "w", stdout) ;
#endif

	int test = 1 , tc = 0 ;
	//Int(test) ;
	while (test--) {
		solve() ;
	}

#ifndef ONLINE_JUDGE
	fprintf(stderr, "\nRuntime: %.10fs\n", (double) (clock() - tStart) / CLOCKS_PER_SEC);
#endif
	return 0 ;
}
