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

const int N          = (int)1e5 + 5 ;
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

ll dp[22][N], cst ;
int n, k, a[N], F[N], s, e ;

struct Cost{
    Cost(){
        s = 1, e = 0 ;
    }
    void add(int id){
        int f = F[a[id]] ;
        cst -= 1LL * f * (f - 1) / 2LL ;
        F[a[id]]++ ;
        cst += 1LL * f * (f + 1) / 2LL ;
    }

    void remove(int id){
        int f = F[a[id]] ;
        cst -= 1LL * f * (f - 1) / 2LL ;
        F[a[id]]-- ;
        --f ;
        cst += 1LL * f * (f - 1) / 2LL ;
    }

    void query(int l, int r){
        while(s > l)add(--s) ;
        while(e < r)add(++e) ;
        while(s < l)remove(s++) ;
        while(e > r)remove(e--) ;
    }
} C ;

void call(int i, int l, int r, int optl, int optr){
    if(l > r)return  ;
    
    int mid = (l + r) >> 1, best = -1 ;
    dp[i][mid] = Inf ;
    for(int j = optl ; j <= min(mid, optr) ; ++j){
        C.query(j + 1 , mid) ;
        if(dp[i - 1][j] + cst < dp[i][mid]){
            dp[i][mid] = dp[i - 1][j] + cst ;
            best = j ;
        }
    }
    //for(int j = optl ; j <= mid ; ++j)F[cur][a[j]]-- ;
    call(i, l, mid - 1, optl, best) ;
    call(i, mid + 1, r, best, optr) ;
}

int main(){
    int test = 1 , tc = 0 ;
    while(test--){
        n = Int, k = Int ;
        for(int i = 1 ; i <= n ; ++i){
            a[i] = Int ;
        }
        vi f(N, 0) ;
        ll cst = 0 ;
        for(int i = 1 ; i <= n ; ++i){
            cst += f[a[i]] ;
            dp[1][i] = cst ;
            ++f[a[i]] ;
        }
        for(int i = 2 ; i <= k ; ++i){
            call(i, 1, n, 1, n) ;
        }
        printf("%lld\n",dp[k][n]);
    }
    return 0 ;
}

/*...Always look at the part - 04...*/
/*...............END................*/


