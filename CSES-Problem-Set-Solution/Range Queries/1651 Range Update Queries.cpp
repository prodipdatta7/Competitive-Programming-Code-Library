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
 
 
struct segment{
    ll tree[N << 2] , lazy[N << 2] ;
    segment(){
        mem(tree) ;
        mem(lazy) ;
    }
    void propagate(int i , int b , int e){
        if(lazy[i]){
            tree[i] += lazy[i] * (e - b + 1) ;
            if(b != e){
                lazy[i << 1] += lazy[i] ;
                lazy[i << 1 | 1] += lazy[i] ;
            }
            lazy[i] = 0 ;
        }
    }
    
    void upd(int i , int b , int e , int l , int r, int v){
        propagate(i, b, e) ;
        if(b > r or e < l)return ;
        if(l <= b and e <= r){
            tree[i] += (e - b + 1) * v ;
            if(b != e){
                lazy[i << 1] += v ;
                lazy[i << 1 | 1] += v ;
            }
            return ;
        }
        int mid = (b + e) >> 1 ;
        upd(i << 1 , b , mid , l , r, v) ;
        upd(i << 1 | 1 , mid + 1 , e , l , r, v) ;
        tree[i] = tree[i << 1] + tree[i << 1 | 1] ;
    }
 
    ll query(int i , int b , int e , int p){
        propagate(i, b, e) ;
        if(b > p or e < p)return 0 ;
        if(b == e)return tree[i] ;
        int mid = (b + e) >> 1 ;
        return query(i << 1 , b , mid , p) + query(i << 1 | 1 , mid + 1 , e , p) ;
    }
}seg;
 
 
 
int main(){
    int test = 1 , tc = 0 ;
    while(test--){
        int n = Int, q = Int ;
        vi a(n + 1) ;
        for(int i = 1 ; i <= n ; ++i){
            a[i] = Int ;
        }
        while(q--){
            int tp = Int ;
            if(tp == 1){
                int x = Int, y = Int , k = Int ;
                seg.upd(1, 1, n, x, y, k) ;
            }
            else {
                int p = Int ;
                cout << seg.query(1, 1, n, p) + a[p] << '\n' ;
            }
        }
    }
    return 0 ;
}
 
/*...Always look at the part - 04...*/
/*...............END................*/
