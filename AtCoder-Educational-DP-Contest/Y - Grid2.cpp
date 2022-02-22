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

int Int(){int x ; scanf("%d",&x) ; return x ;}
ll Long(){ll x ; scanf("%lld",&x) ; return x ;}

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
const int  Mod       = (int)1e9 + 7 ;
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

int fact[N] ;

inline int mul(int a, int b){
    return (ll)a * b % Mod ;
}

inline int sub(int a, int b){
    a -= b ;
    if(a < 0)a += Mod ;
    return a ;
}

inline int modpow(int b, int p){
    int res = 1 ;
    while(p){
        if(p & 1)res = mul(res, b) ;
        b = mul(b, b) ;
        p >>= 1 ;
    }
    return res ;
}

void factorial(){
    fact[0] = 1 ;
    for(int i = 1 ; i < N ; ++i){
        fact[i] = mul(fact[i - 1], i) ;
    }
}

int res(int x, int y){
    return mul(fact[x + y], modpow(mul(fact[x], fact[y]), Mod - 2)) ;
}

int main(){
    factorial() ;
    int test = 1 , tc = 0 ;
    while(test--){
        int n = Int, m = Int, k = Int ;
        vector< pii > v;
        for(int i = 1 ; i <= k ; ++i){
            v.pb({Int, Int}) ;
        }
        v.pb({n, m}) ;
        sort(all(v)) ;
        vi ans(k + 1) ;
        for(int i = 0 ; i <= k ; ++i){
            ans[i] = res(v[i].ff - 1, v[i].ss - 1) ;
        }
        for(int i = 0 ; i < k ; ++i){
            for(int j = i + 1 ; j <= k ; ++j){
                if(v[j].ff < v[i].ff or v[j].ss < v[i].ss)continue ;
                ans[j] = sub(ans[j], mul(ans[i], res(v[j].ff - v[i].ff, v[j].ss - v[i].ss))) ;
            }
        }
        cout << ans[k] << '\n' ;
    }
    return 0 ;
}

/*...Always look at the part - 04...*/
/*...............END................*/


