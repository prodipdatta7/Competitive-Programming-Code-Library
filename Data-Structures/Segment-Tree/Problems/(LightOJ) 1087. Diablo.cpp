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

const int max_n = 150000 ;

struct segmentTree {
    int tree[N << 2] ;
    void clear() {
        mem(tree) ;
    }
    void upd(int i , int b , int e , int p, int c) {
        if (b > p or e < p)return ;
        if (b == e) {
            tree[i] += c ;
            return ;
        }
        int mid = (b + e) >> 1 ;
        upd(i << 1 , b , mid , p , c) ;
        upd(i << 1 | 1 , mid + 1 , e , p , c) ;
        tree[i] = tree[i << 1] + tree[i << 1 | 1] ;
    }

    int query(int i , int b , int e , int k) {
        if (b == e)return b ;
        int mid = (b + e) >> 1 ;
        if (tree[i << 1] >= k)return query(i << 1, b, mid, k) ;
        else return query(i << 1 | 1, mid + 1, e, k - tree[i << 1]) ;
    }
} seg;



int main() {
    int test = Int , tc = 0 ;
    while (test--) {
        vi a ;
        int n = Int, q = Int ;
        seg.clear() ;
        for (int i = 1 ; i <= n ; ++i) {
            a.pb(Int) ;
            seg.upd(1, 1, max_n, i, 1) ;
        }
        printf("Case %d:\n", ++tc);
        char c[3] ;
        int x ;
        while (q--) {
            scanf("%s%d", c, &x) ;
            if (c[0] == 'c') {
                int f = seg.query(1, 1, max_n, x) ;
                if (f > sz(a))puts("none") ;
                else {
                    printf("%d\n", a[f - 1]);
                    seg.upd(1, 1, max_n, f, -1) ;
                }
            }
            else {
                ++n ;
                a.pb(x) ;
                seg.upd(1, 1, max_n, n, 1) ;
            }
        }
    }
    return 0 ;
}

/*...Always look at the part - 04...*/
/*...............END................*/


