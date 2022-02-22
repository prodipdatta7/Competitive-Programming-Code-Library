/**
 *  “Experience is the name everyone gives to their mistakes.” – Oscar Wilde
 *
 *  author  :   prodipdatta7
 *  created :   Sunday 01-March, 2020  10:43:56 AM
**/

#include <bits/stdc++.h>
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

#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) {cout << endl ;}
template<TN T, TN... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cerr << *it << " = " << a << ' ' ;
    err(++it, args...);
}

/*###############-> Constraints <-###############*/

const int N          = (int)2e5 + 5 ;
const int maxN       = (int)1e6 + 6 ;
const ll  Mod        = (ll)1e9 + 7 ;
const int inf        = (int)2e9 ;
const ll  Inf        = (ll)1e18 ;
const int mod        = (int)1e9 + 7 ;

inline int add(int a, int b, int mod) {a += b ; return a >= mod ? a - mod : a ;}
inline int sub(int a, int b, int mod) {a -= b ; return a < 0 ? a + mod : a ;}
inline int mul(int a, int b, int mod) {return (ll)a * b % mod ;}

/*...... ! Code starts from here ! ......*/

int backEdges[N], level[N], cycleID[N], n, m, old ;
int par[N][20], dep[N], powersOftwo[N] ;
vvi g ;

void dfs(int s, int p = 0) {
    level[s] = 1 + level[p] ;
    cycleID[s] = s ;
    for (int i : g[s]) {
        if (!level[i]) {
            dfs(i, s) ;
            backEdges[s] += backEdges[i] ;
            if (backEdges[i])cycleID[s] = cycleID[i] ;
        }
        else {
            if (i == p)continue ;
            if (level[i] < level[s]) { // back-edges going up from s .
                ++backEdges[s] ;
                cycleID[s] = ++n ;
            }
            else { // level[i] > level[s] , back-edges going down from s .
                --backEdges[s] ;
                cycleID[s] = cycleID[i] ;
            }
        }
    }
}

void build(int s, int p = 0) {
    level[s] = 1 + level[p] ;
    dep[s] = dep[p] + (s > old) ;
    par[s][0] = p ;
    for (int i = 1 ; i < 20 ; ++i) {
        par[s][i] = par[par[s][i - 1]][i - 1] ;
    }
    for (int i : g[s]) {
        if (i == p)continue ;
        build(i, s) ;
    }
}

int LCA(int a, int b) {
    if (level[a] < level[b])swap(a, b) ;
    int d = level[a] - level[b] ;
    for (int i = 19 ; i >= 0 ; --i) {
        if (d >> i & 1)a = par[a][i] ;
    }
    if (a == b)return a ;
    for (int i = 19 ; i >= 0 ; --i) {
        if (par[a][i] != par[b][i]) {
            a = par[a][i], b = par[b][i] ;
        }
    }
    return par[a][0] ;
}

int main() {
    // ios_base::sync_with_stdio(false) ;
    // cin.tie(NULL) ; cout.tie(NULL) ;
    int test = 1 , tc = 0 ;
    //Int(test) ;
    while (test--) {
        Int(n, m) ;
        old = n ;
        g.resize(n + 1) ;
        vector < pii > edges ;
        for (int i = 1 ; i <= m ; ++i) {
            int x, y ; Int(x, y) ;
            g[x].pb(y) ;
            g[y].pb(x) ;
            edges.push_back(make_pair(x, y)) ;
        }
        dfs(1) ;
        g.clear() ;
        g.resize(n + 1) ;
        int id = n + 1 ;
        for (pii &i : edges) {
            i.ff = cycleID[i.ff], i.ss = cycleID[i.ss] ;
            id = i.ff ;
            if (i.ff == i.ss)continue ;
            g[i.ff].push_back(i.ss) ;
            g[i.ss].push_back(i.ff) ;
        }
        build(id) ;
        powersOftwo[0] = 1 ;
        int till = 0 ;
        int q ; Int(q) ;
        while (q--) {
            int x, y ; Int(x, y) ;
            x = cycleID[x], y = cycleID[y] ;
            if (x == y)puts("2") ;
            else {
                int lca = LCA(x, y) ;
                int cnt = dep[x] + dep[y] - dep[lca] - dep[par[lca][0]] ;
                while (till < cnt)powersOftwo[++till] = mul(powersOftwo[till - 1], 2, mod) ;
                printf("%d\n", powersOftwo[cnt]);
            }
        }
    }
    return 0 ;
}
