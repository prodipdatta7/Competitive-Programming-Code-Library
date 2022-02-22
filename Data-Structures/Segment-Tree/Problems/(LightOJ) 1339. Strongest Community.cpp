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

const int N          = (int)1e5 + 5 ;
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


struct segmentTree {
    int a[N] ;
    struct data {
        int l, r, lmx, rmx, res ;
        data(): l(0), r(0), lmx(0), rmx(0), res(0) {}
        data(int l, int r, int lmx, int rmx, int res): l(l), r(r), lmx(lmx), rmx(rmx), res(res) {}
    } ;
    vector < data > T ;
    void clear(int n) {
        T.clear() ;
        T.resize(n << 2) ;
    }

    data modify(data a, data b) {
        if (a.res == 0)return b ;
        else if (b.res == 0)return a ;
        data c ;
        c.res = max(a.res, b.res) ;
        int cc = max(max(a.lmx, a.rmx), max(b.lmx, b.rmx)) ;
        c.res = max(c.res, cc) ;
        c.lmx = a.lmx, c.rmx = b.rmx, c.l = a.l, c.r = b.r ;
        if (a.r == b.l) {
            c.res = max(c.res, a.rmx + b.lmx) ;
            if (a.l == a.r)c.lmx = a.lmx + b.lmx ;
            if (b.l == b.r)c.rmx = b.rmx + a.rmx ;
        }
        return c ;
    }

    void build(int i , int b , int e) {
        if (b == e) {
            T[i] = data(a[b], a[b], 1, 1, 1) ;
            return ;
        }

        int mid = (b + e) >> 1 ;
        build(i << 1 , b , mid) ;
        build(i << 1 | 1 , mid + 1 , e) ;
        T[i] = modify(T[i << 1], T[i << 1 | 1]) ;
    }

    data query(int i , int b , int e , int l , int r) {
        if (b > r or e < l)return data(0, 0, 0, 0, 0) ;
        if (l <= b and e <= r)return T[i] ;
        int mid = (b + e) >> 1 ;
        data a = query(i << 1 , b , mid , l , r) ;
        data ab = query(i << 1 | 1 , mid + 1 , e , l , r) ;
        return modify(a, ab) ;
    }
    int get(int n, int l, int r) {
        data c = query(1, 1, n, l, r) ;
        return c.res ;
    }
} seg;



int main() {
    int test = Int , tc = 0 ;
    while (test--) {
        int n = Int, c = Int, q = Int ;
        seg.clear(n + 1) ;
        for (int i = 1 ; i <= n ; ++i) {
            seg.a[i] = Int ;
        }
        seg.build(1, 1, n) ;
        printf("Case %d:\n", ++tc);
        while (q--) {
            int l = Int, r = Int ;
            printf("%d\n", seg.get(n, l, r));
        }
    }
    return 0 ;
}

/*...Always look at the part - 04...*/
/*...............END................*/


