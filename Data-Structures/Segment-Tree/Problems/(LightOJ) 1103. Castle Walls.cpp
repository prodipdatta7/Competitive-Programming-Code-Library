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
typedef pair<int, int>           pii ;
typedef pair<ll, ll>             pll ;
typedef vector<int>             vi ;
typedef vector<ll>              vll ;
typedef vector<vector<int>>     vvi ;

int Int() {int x ; scanf("%d", &x) ; return x ;}
ll Long() {ll x ; scanf("%lld", &x) ; return x ;}

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

vector < vector < int > > T ;
int a[N] ;

void build(int i, int b, int e) {
    if (b == e) {
        if (a[b])T[i].pb(a[b]) ;
        return ;
    }
    int mid = (b + e) >> 1 ;
    build(i << 1, b, mid) ;
    build(i << 1 | 1, mid + 1, e) ;
    merge(all(T[i << 1]), all(T[i << 1 | 1]), back_inserter(T[i])) ;
}

int query(int i, int b, int e, int l, int r, int v, int tp) {
    if (e < l or b > r)return 0 ;
    if (l <= b and e <= r) {
        if (tp == 1) return upper_bound(all(T[i]), v) - T[i].begin() ;
        return T[i].end() - lower_bound(all(T[i]), v) ;
    }
    int mid = (b + e) >> 1 ;
    return query(i << 1, b, mid, l, r, v, tp) + query(i << 1 | 1, mid + 1, e, l, r, v, tp) ;
}

int main() {
    int test = Int , tc = 0 ;
    while (test--) {
        int n = Int, m = Int ;
        T.clear() ;
        T.resize((n + m) << 2) ;
        mem(a) ;
        for (int i = 1 ; i <= n ; ++i) {
            int x = Int, y = Int ;
            a[y] = x ;
        }
        build(1, 1, n + m) ;
        ll res = 0 ;
        for (int i = 1 ; i <= m ; ++i) {
            int x = Int, y = Int ;
            res += query(1, 1, n + m, y, n + m, x, 1) ;
            res += query(1, 1, n + m, 1, y, x + 1, 0) ;
        }
        printf("Case %d: %lld\n", ++tc, res);
    }
    return 0 ;
}

/*...Always look at the part - 04...*/
/*...............END................*/


