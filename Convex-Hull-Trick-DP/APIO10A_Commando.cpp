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

//* Description: Container where you can add lines of the form (mx + c), and query maximum values at points x.**//

bool tp ;
struct Line{
    mutable ll m, c, p ;
    bool operator<(const Line& u)const{return tp ? p < u.p :  m < u.m ;}
    bool operator<(ll u){return p < u ;}
} ;

struct DynamicCHT : multiset< Line > {
    
    ll div(ll a, ll b){
        return a / b - ((a ^ b) < 0 and (a % b)) ;
    }
    bool intersect(iterator x, iterator y){
        if(y == end()){ x -> p = inf ; return false ;}
        if(x -> m == y -> m)x -> p = x -> m >= y -> m ? Inf : -Inf ;
        else x -> p = div(x -> c - y -> c, y -> m - x -> m) ;
        return x -> p >= y -> p ;
    }
    void add(ll x, ll y){
        auto c = insert({x, y, 0}), b = c++, a = b ;
        while(intersect(b, c))c = erase(c) ;
        if(a != begin() and intersect(--a, b))intersect(a, b = erase(b)) ;
        while((b = a) != begin() and (--a) -> p >= b -> p)
            intersect(a, erase(b)) ;
    }
    ll query(ll x){
        assert(!empty()) ;
        tp = 1 ;
        auto u = *lower_bound({0, 0, x}) ;
        tp = 0 ;
        return u.m * x + u.c ;
    }
} ;

int main(){
    int test = Int , tc = 0 ;
    while(test--){
        DynamicCHT cht ;
        int n = Int, x = Int, y = Int, z = Int ;
        vll a(n + 1), p(n + 1,0); 
        ll res = 0 ;
        for(int i = 1 ; i <= n ; ++i){
            a[i] = Int ;
            p[i] = p[i - 1] + a[i] ;
        }
        cht.add(0, 0) ;
        for(int i = 1 ; i <= n ; ++i){
            res = cht.query(p[i]) + x * p[i] * p[i] + p[i] * y + z ;
            cht.add(-2LL * p[i] * x, res + p[i] * (x * p[i] - y)) ;
        }
        printf("%lld\n",res);
    }
    return 0 ;
}

/*...Always look at the part - 04...*/
/*...............END................*/



