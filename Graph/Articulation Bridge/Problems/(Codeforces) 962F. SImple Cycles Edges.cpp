/**
 *  “Experience is the name everyone gives to their mistakes.” – Oscar Wilde
 *
 *  author  :   prodipdatta7
 *  created :   Monday 02-March, 2020  02:11:38 PM
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

const int N          = (int)1e5 + 5 ;
const int maxN       = (int)1e6 + 6 ;
const ll  Mod        = (ll)1e9 + 7 ;
const int inf        = (int)2e9 ;
const ll  Inf        = (ll)1e18 ;
const int mod        = (int)1e9 + 7 ;

inline int add(int a, int b, int mod) {a += b ; return a >= mod ? a - mod : a ;}
inline int sub(int a, int b, int mod) {a -= b ; return a < 0 ? a + mod : a ;}
inline int mul(int a, int b, int mod) {return (ll)a * b % mod ;}

/*...... ! Code starts from here ! ......*/

int level[N], backEdges[N], total, par[N], ID[N], root[N] ;
vector < vector < pii > > g ;
pair < int , int > edges[N] ;
int backEdge[N] ;

void dfs(int s, int id, int p = 0) {
    level[s] = 1 + level[p] ;
    par[s] = p ;
    ID[s] = id ;
    for (pii i : g[s]) {
        if (i.ff == p)continue ;
        if (!level[i.ff]) {
            dfs(i.ff, i.ss, s) ;
            backEdges[s] += backEdges[i.ff] ;
        }
        else {
            
            if (level[i.ff] > level[s])--backEdges[s] ;
            else {
                backEdge[++total] = i.ss ;
                if (edges[i.ss].ff != s)swap(edges[i.ss].ff, edges[i.ss].ss) ;
                ++backEdges[s] ;
            }
        }
    }
}

void build(int s, int p = 0) {
    level[s] = 1 + level[p] ;
    if (backEdges[s] == 1 and level[s] > 1) {
        root[s] = root[p] ;
    }
    else root[s] = s ;
    for (pii i : g[s]) {
        if (!level[i.ff]) {
            build(i.ff, s) ;
        }
    }
}

int main() {
    // ios_base::sync_with_stdio(false) ;
    // cin.tie(NULL) ; cout.tie(NULL) ;
    int test = 1 , tc = 0 ;
    //Int(test) ;
    while (test--) {
        int n, m ; Int(n, m) ;
        g.resize(n + 1) ;
        for (int i = 1 ; i <= m ; ++i) {
            int x, y ; Int(x, y) ;
            g[x].pb(make_pair(y, i)) ;
            g[y].pb(make_pair(x, i)) ;
            edges[i] = make_pair(x, y) ;
        }
        for (int i = 1 ; i <= n ; ++i) {
            if (!level[i])dfs(i, 0) ;
        }
        mem(level) ;
        for (int i = 1 ; i <= n ; ++i) {
            if (!level[i])build(i) ;
        }
        //for (int i = 1 ; i <= n ; ++i)error(level[i], root[i], backEdges[i])
        vi res ;
        for (int i = 1 ; i <= total ; ++i) {
            int u = edges[backEdge[i]].ff, v = edges[backEdge[i]].ss ;
            if (root[u] == root[v]) {
                res.pb(backEdge[i]) ;
                while (u != v) {
                    res.pb(ID[u]) ;
                    u = par[u] ;
                }
            }
        }
        sort(all(res)) ;
        cout << sz(res) << '\n' ;
        for (int i : res)cout << i << ' ' ;
        cout << '\n' ;
    }
    return 0 ;
}
