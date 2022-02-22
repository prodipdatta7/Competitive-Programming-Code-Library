//problem link : https://www.spoj.com/problems/CPCRC1C/
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
/*#include <bits/stdc++.h>*/
using namespace std ;

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
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) {cout << endl ;}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cerr << *it << " = " << a << ' ' ;
    err(++it, args...);
}

const int N         = (int)2e5 + 5 ;
const int maxN      = (int)1e6 + 6 ;
const ll Mod        = (ll)998244353 ;

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

ll dp[19][172][2] ;
int k , len ;
string a , b , c ;

ll call(int cur , int sum , int R){
    if(cur == len){
        return sum;
    }
    ll &ret = dp[cur][sum][R] ;
    if(ret != -1)return ret ;
    ret = 0 ;
    int r ;
    r = (R) ? c[cur] - '0' : 9 ;
    for(int i = 0 ; i <= r ; i++){
        ret += call(cur + 1 , sum + i , R and r == i) ;
        //ret %= Mod ;
    }
    return ret ;
}

int main(){
    int test = 1 , tc = 0 ;
    while(cin >> a >> b){
        if(a[0] == '-')break ;
        len = sz(b) ;
        c = b ;
        memset(dp , -1 , sizeof dp) ;
        ll ans1 = call(0 , 0 , 1) ;
        len = sz(a) ;
        c = a ;
        memset(dp , -1 , sizeof dp) ;
        ll res2 = call(0 , 0 , 1) ;
        for(int i = 0 ; a[i] ; i++){
            res2 -= a[i] - '0' ;
        }
        cout << ans1 - res2 << '\n' ;
    }
    return 0 ;
}
