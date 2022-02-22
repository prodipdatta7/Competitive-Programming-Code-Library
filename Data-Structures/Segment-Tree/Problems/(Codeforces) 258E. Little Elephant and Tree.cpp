/**
 *  “Experience is the name everyone gives to their mistakes.” – Oscar Wilde
 *
 *  author  :   prodipdatta7
 *  created :   Tuesday 03-March, 2020  11:15:30 AM
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

int st[N], en[N], pos, n, m, res[N] ;
vvi g, query ;

void dfs(int s, int p = 0) {
    st[s] = ++pos ;
    for (int i : g[s]) {
        if (i == p)continue ;
        dfs(i, s) ;
    }
    en[s] = pos ;
}

struct data {
    int covered ;
    int sum, backup ;
} ;

data T[N << 2] ;

void merge(data &a, data &b, data &c, int val) {
    a.backup = b.sum + c.sum ;
    if (a.covered)a.sum = val ;
    else a.sum = a.backup ;
}

void update(int i, int b, int e, int l, int r, int v) {
    if (l > e or b > r)return ;
    if (l <= b and e <= r) {
        T[i].covered += v ;
        if (T[i].covered)T[i].sum = e - b + 1 ;
        else T[i].sum = T[i].backup ;
        return ;
    }
    int mid = (b + e) >> 1 ;
    update(i << 1, b, mid, l, r, v) ;
    update(i << 1 | 1, mid + 1, e, l, r, v) ;
    merge(T[i], T[i << 1], T[i << 1 | 1], e - b + 1) ;
}

void conquere(int s, int p = 0) {
    for (int i : query[s]) {
        update(1, 1, n, st[i], en[i], 1) ;
        update(1, 1, n, st[s], en[s], 1) ;
    }
    res[s] = T[1].sum ;
    for (int i : g[s]) {
        if (i == p)continue ;
        conquere(i, s) ;
    }
    for (int i : query[s]) {
        update(1, 1, n, st[i], en[i], -1) ;
        update(1, 1, n, st[s], en[s], -1) ;
    }
}

int main() {
    // ios_base::sync_with_stdio(false) ;
    // cin.tie(NULL) ; cout.tie(NULL) ;
    int test = 1 , tc = 0 ;
    //Int(test) ;
    while (test--) {
        Int(n, m) ;
        g.resize(n + 1) ;
        for (int i = 1 ; i < n ; ++i) {
            int x, y ; Int(x, y) ;
            g[x].push_back(y) ;
            g[y].push_back(x) ;
        }
        dfs(1) ;
        query.resize(n + 1) ;
        for (int i = 1 ; i <= m ; ++i) {
            int x, y ; Int(x, y) ;
            query[x].push_back(y) ;
            query[y].push_back(x) ;
        }
        conquere(1) ;
        for (int i = 1 ; i <= n ; ++i)cout << (res[i] ? res[i] - 1 : 0) << " \n"[i == n] ;
    }
    return 0 ;
}
