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

const int N          = (int)1e6 + 5 ;
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

ll a[N], b[N], c[N] ;
int ind[N] ;

struct CHT{
    //** Decreasing slope and max query **//
    vector< ll > m, c ;
    bool bad(int f1, int f2, int f3){
        return 1.0 * (c[f3] - c[f1]) * (m[f1] - m[f2]) >= 1.0 * (c[f2] - c[f1]) * (m[f1] - m[f3]) ;
    }
    void add(ll x, ll y){
        m.pb(x), c.pb(y) ;
        int ss = sz(m) ;
        while(ss >= 3 and bad(ss - 3, ss - 2, ss - 1)){
            m.erase(m.end() - 2) ;
            c.erase(c.end() - 2) ;
            --ss ;
        }
    }
    ll f(int i, ll x){return m[i] * x + c[i] ;}
    ll query(ll x){
        int l = 0, r = sz(m) - 1, id ;
        ll res = 0 ;
        while(l <= r){
            int del = (r - l) / 3, mid1 = l + del, mid2 = r - del ;
            ll y1 = f(mid1, x), y2 = f(mid2, x) ;
            if(y1 >= y2)res = y1, r = mid2 - 1 ;
            else res = y2, l = mid1 + 1 ;
        }
        return res ;
    }
}ds ;

int main(){
    int test = 1 , tc = 0 ;
    while(test--){
        int n = Int ;
        for(int i = 1 ; i <= n ; ++i){
            a[i] = Int, b[i] = Int, c[i] = Long ;
            ind[i] = i ;
        }
        sort(ind + 1, ind + n + 1, [](int i, int j){
            return a[i] < a[j] ;
        }) ;
        ds.add(0, 0) ;
        ll res = 0 ;
        for(int i = 1 ; i <= n ; ++i){
            ll k = 1LL * a[ind[i]] * b[ind[i]] - c[ind[i]] ;
            k += ds.query(b[ind[i]]) ;
            ds.add(-a[ind[i]], k) ;
            res = max(res, k) ;
        }
        printf("%lld\n",res);
    }
    return 0 ;
}

/*...Always look at the part - 04...*/
/*...............END................*/



