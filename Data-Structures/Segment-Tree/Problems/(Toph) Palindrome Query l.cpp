/**
     *  “Experience is the name everyone gives to their mistakes.” – Oscar Wilde
     *
     *  Prodip Datta
     *  Dept. Of Computer Science & Engineering
     *  Session: 2014-15
     *  email  : prodipdatta7@gmail.com
     *  Bangabandhu Sheikh Mujibur Rahman Science & Technology University, Gopalganj-8100.
     *
     *  created : Friday 09-April, 2021  03:11:52 PM
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
#include <functional>
#include <numeric>
#include <utility>
#include <limits>
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
#define     pii         pair< int, int >
#define     pll         pair< ll, ll >
#define     vi          vector< int >
#define     vll         vector< ll >
#define     vvi         vector< vector< int > >
#define     vvii         vector< vector< pii > >
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

typedef tree <pii, null_type, less< pii >, rb_tree_tag, tree_order_statistics_node_update > ordered_set;
typedef tree <pii, null_type, less_equal< pii >, rb_tree_tag, tree_order_statistics_node_update > ordered_multiset;

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
template<typename T, typename U> inline void cmin(T &x, U y) { if (y < x) x = y; }
template<typename T, typename U> inline void cmax(T &x, U y) { if (x < y) x = y; }

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
const double PI      = (double)acos(-1.0) ;


inline int add(int a, int b, int mod) {a += b ; return a >= mod ? a - mod : a ;}
inline int sub(int a, int b, int mod) {a -= b ; return a < 0 ? a + mod : a ;}
inline int mul(int a, int b, int mod) {return (ll)a * b % mod ;}

/*...... ! Code starts from here ! ......*/

int n ;
char s[N] ;

const int bases[2] = {31, 151};
const int mods[2] = {1000000123, 1000000321};
unsigned long long base = 37, basePower[N] ;
int basePowers[2][N] ;

void generatePowers() {
	basePowers[0][0] = 1 ;
	basePowers[1][0] = 1 ;
	basePower[0] = 1 ;
	for (int i = 1 ; i < N ; ++i) {
		for (int j = 0 ; j < 2 ; ++j) {
			basePowers[j][i] = mul(basePowers[j][i - 1], bases[j], mods[j]) ;
		}
		basePower[i] = basePower[i - 1] * base ;
	}
}

struct Node {
	int length;
	vector < int > forwardHash ;
	vector < int > backwardHash ;
	unsigned long long ForwardHash, BackwardHash ;
	bool used = false ;
	Node() {
		length = 0 ;
		forwardHash.assign(2, 0);
		backwardHash.assign(2, 0);
		ForwardHash = BackwardHash = 0;
		used = false ;
	}
	Node(int _len, int v, unsigned long long _v) {
		length = _len ;
		forwardHash.assign(2, v) ;
		backwardHash.assign(2, v) ;
		ForwardHash = BackwardHash = _v;
		used = _len > 0 ;
	}
	Node merge(Node other) {
		if (!used)return other ;
		if (!other.used)return *this;
		Node cur ;
		cur.used = true ;
		cur.length = length + other.length ;
		for (int i = 0;  i < 2 ; ++i) {
			cur.forwardHash[i] = add(forwardHash[i], mul(other.forwardHash[i], basePowers[i][length], mods[i]), mods[i]) ;
			cur.backwardHash[i] = add(other.backwardHash[i], mul(backwardHash[i], basePowers[i][other.length], mods[i]), mods[i]) ;
		}
		cur.ForwardHash = ForwardHash + (other.ForwardHash * basePower[length]) ;
		cur.BackwardHash = other.BackwardHash + (BackwardHash * basePower[other.length]) ;
		return cur ;
	}
} ;

vector < Node > T ;

void build(int i = 1 , int b = 1, int e = n) {
	if (b == e) {
		int v = s[b] - 'a' + 1 ;
		T[i] = Node(1, v, v) ;
		return ;
	}
	int mid = b + e >> 1 ;
	build(i << 1, b, mid) ;
	build(i << 1 | 1, mid + 1, e) ;
	T[i] = T[i << 1].merge(T[i << 1 | 1]) ;
}

void update(int p, int v, int tp, int i = 1, int b = 1, int e = n) {
	if (b == e) {
		// if(!tp)error(p, v, tp)
		T[i] = Node(tp, v, v) ;
		return ;
	}
	int mid = b + e >> 1 ;
	if (T[i << 1].length >= p)update(p, v, tp, i << 1, b, mid);
	else update(p - T[i << 1].length, v, tp, i << 1 | 1, mid + 1, e);
	T[i] = T[i << 1].merge(T[i << 1 | 1]) ;
}

Node query(int l, int r, int i = 1, int b = 1, int e = n) {
	if (l > e or r < b)return Node() ;
	if (l <= b and e <= r)return T[i];
	int mid = b + e >> 1 ;
	return query(l, r, i << 1, b, mid).merge(query(l, r, i << 1 | 1, mid + 1, e)) ;
}

int getPos(int p, int i = 1, int b = 1, int e = n) {
	if (b == e)return b ;
	int mid = b + e >> 1 ;
	if (T[i << 1].length >= p)return getPos(p, i << 1, b, mid) ;
	else return getPos(p - T[i << 1].length, i << 1 | 1, mid + 1, e) ;
}

bool isPalindrome(Node value) {
	bool alright = true ;
	for (int i = 0 ; i < 1 ; ++i) {
		alright &= (value.forwardHash[i] == value.backwardHash[i]) ;
	}
	// alright &= (value.ForwardHash == value.BackwardHash) ;
	return alright ;
}

int main() {
#ifndef ONLINE_JUDGE
	clock_t tStart = clock();
	//freopen("input.txt", "r", stdin) ;
	//freopen("output.txt", "w", stdout) ;
#endif
	int test = 1 , tc = 0 ;
	// Int(test) ;
	generatePowers() ;
	while (test--) {
		scanf("%s", s + 1) ;
		n = strlen(s + 1) ;
		T.assign((n << 2) + 2, Node()) ;
		build() ;
		int q ; Int(q) ;
		string tp, c;
		int p ;
		while (q--) {
			cin >> tp ;
			if (tp[0] == 'U') {
				cin >> p >> c;
				update(p, c[0] - 'a' + 1, 1) ;
			}
			else if (tp[0] == 'D') {
				Int(p) ;
				update(p, 0, 0) ;
			}
			else {
				int l, r ; Int(l, r) ;

				l = getPos(l), r = getPos(r) ;
				// error(l, r)
				Node value = query(l, r) ;
				if (isPalindrome(value))puts("Yes!") ;
				else puts("No!") ;
			}
		}
	}

#ifndef ONLINE_JUDGE
	fprintf(stderr, "\nRuntime: %.10fs\n", (double) (clock() - tStart) / CLOCKS_PER_SEC);
#endif
	return 0 ;
}
