/**
 *  “Experience is the name everyone gives to their mistakes.” – Oscar Wilde
 *
 *  author  :   prodipdatta7
 *  created :   Tuesday 03-March, 2020  12:24:26 AM
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

int height[N], total ;
pair < int, int > edge[N], answer[N] ;
vector < vector < pii > > g ;

int dfs(int s, int p = 0){
    height[s] = 1 + height[p] ;
    vector < int > backEdge ;
    for(pii i : g[s]){
        if(i.ff == p)continue ;
        if(!height[i.ff]){
            int output = dfs(i.ff, s) ;
            if(output){
                answer[++total] = make_pair(i.ss, output) ;
            }
            else backEdge.push_back(i.ss) ;
        }
        else {
            if(height[i.ff] < height[s]){
                backEdge.push_back(i.ss) ;
            }
        }
    }
    int len = sz(backEdge) ;
    for(int i = 0 ; i < len - 1 ; i += 2){
        answer[++total] = make_pair(backEdge[i], backEdge[i + 1]) ;
    }
    return (len & 1) ? backEdge.back() : 0 ;
}

int main() {
    // ios_base::sync_with_stdio(false) ;
    // cin.tie(NULL) ; cout.tie(NULL) ;
    int test = 1 , tc = 0 ;
    //Int(test) ;
    while (test--) {
        int n, m ; Int(n, m) ;
        g.resize(n + 1) ;
        for(int i = 1 ; i <= m ; ++i){
            int x, y ; Int(x, y) ;
            edge[i] = make_pair(x, y) ;
            g[x].push_back(make_pair(y, i)) ;
            g[y].push_back(make_pair(x, i)) ;
        }
        for(int i = 1 ; i <= n ; ++i){
            if(!height[i])dfs(i, 0) ;
        }
        printf("%d\n",total);
        for(int i = 1 ; i <= total ; ++i){
            int x = answer[i].ff, y = answer[i].ss ;
            vi cur ;
            cur.push_back(edge[x].ff) ;
            cur.push_back(edge[x].ss) ;
            cur.push_back(edge[y].ff) ;
            cur.push_back(edge[y].ss) ;
            sort(all(cur)) ;
            if(cur[0] == cur[1])swap(cur[0], cur[3]) ;
            else if(cur[1] == cur[2])swap(cur[2], cur[3]) ;
            else swap(cur[1], cur[2]) ;
            printf("%d %d %d\n", cur[0], cur[1], cur[2]);
        }
    }
    return 0 ;
}
