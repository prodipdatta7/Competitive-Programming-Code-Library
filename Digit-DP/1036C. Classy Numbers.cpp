//problem link : http://codeforces.com/contest/1036/problem/C
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
const ll Mod        = (ll)1e9 + 7 ;

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
string l , r , c ;

ll dp[20][4][2] ;
int len ;

ll call(int cur , int bound , int f){
    if(bound > 3)return 0 ;
    if(cur == len){
        return 1 ;
    }
    ll& ret = dp[cur][bound][f] ;
    if(~ret)return ret ;
    ret = 0 ;
    int L = (f) ? c[cur] - '0' : 9 ;
    for(int i = 0 ; i <= L ; i++){
        if(bound + (i > 0) <= 3)ret += call(cur + 1 , bound + (i > 0) , f and i == L) ;
    }
    return ret ;
}

int main(){
    int test = Int , tc = 0 ;
    while(test--){
        cin >> l >> r ;
        len = sz(r) ;
        c = r ;
        memset(dp , -1 , sizeof dp) ;
        ll res = call(0 , 0 , 1) ;
        memset(dp , -1 , sizeof dp) ;
        c = l ;
        len = sz(l) ;
        res -= call(0 ,0 ,1) ;
        int cnt = 0 ;
        for(int i = 0 ; l[i] ; i++){
            if(l[i] != '0')cnt++ ;
        }
        res += (cnt <= 3) ;
        cout << res << '\n' ;
    }
    return 0 ;
}
