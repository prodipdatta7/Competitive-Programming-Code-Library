#include <bits/stdc++.h>
 
using namespace std ;
 
#define     ll          long long
#define     ld          long double
#define     ull         unsigned long long
#define     pii         pair<int,int>
#define     pll         pair<ll,ll>
#define     vi          vector<int>
#define     vll         vector<ll>
#define     vvi         vector<vector<int>>
#define     debug(x)    cerr << #x << " = " << x << '\n' ;
#define     rep(i,b,e)  for(__typeof(e) i = (b) ; i != (e + 1) - 2 * ((b) > (e))  ; i += 1 - 2 * ((b) > (e)))
#define     all(x)      x.begin() , x.end()
#define     rall(x)     x.rbegin() , x.rend()
#define     sz(x)       (int)x.size()
#define     ff          first
#define     ss          second
#define     pb          push_back
#define     eb          emplace_back
#define     mem(a)      memset(a , 0 ,sizeof a)
#define     memn(a)     memset(a , -1 ,sizeof a)
#define     fread       freopen("input.txt","r",stdin)
#define     fwrite      freopen("output.txt","w",stdout)
#define     TN          typename
 
template <TN T> inline void Int(T &a) {
    bool minus = false; a = 0; char ch = getchar();
    while (true) { if (ch == '-' or (ch >= '0' && ch <= '9')) break; ch = getchar(); }
    if (ch == '-') minus = true; else a = ch - '0';
    while (true) { ch = getchar(); if (ch < '0' || ch > '9') break; a = a * 10 + (ch - '0'); }
    if (minus)a *= -1 ;
}
template < TN T, TN T1 > inline void Int(T &a, T1 &b) {Int(a), Int(b) ;}
template < TN T, TN T1, TN T2 > inline void Int(T &a, T1 &b, T2 &c) {Int(a, b), Int(c) ;}
template < TN T, TN T1, TN T2, TN T3 > inline void Int(T &a, T1 &b, T2 &c, T3 &d) {Int(a, b), Int(c, d) ;}
template < TN T, TN T1, TN T2, TN T3, TN T4> inline void Int(T &a, T1 &b, T2 &c, T3 &d, T4 &e) {Int(a, b), Int(c, d, e) ;}
 
/*###############-> Constraints <-###############*/
 
const int N          = (int)5e4 + 5 ;
const int maxN       = (int)1e6 + 6 ;
const ll  Mod        = (ll)1e9 + 7 ;
const int inf        = (int)2e9 ;
const ll  Inf        = (ll)1e18 ;
const int mod        = (int)1e9 + 7 ;
 
inline int add(int a, int b, int mod) {a += b ; return a >= mod ? a - mod : a ;}
inline int sub(int a, int b, int mod) {a -= b ; return a < 0 ? a + mod : a ;}
inline int mul(int a, int b, int mod) {return (ll)a * b % mod ;}
 
/*...... ! Code starts from here ! ......*/
 
struct data{
	int suffix, prefix, total, res ;
	data(int suff = -inf, int pre = -inf, int tot = 0, int ans = 0):suffix(suff), prefix(pre), total(tot), res(ans){}
} ;
 
data T[N << 2] ;
int a[N] ;
 
data merge(data a, data b){
	if(a.suffix == -inf)return b ;
	if(b.suffix == -inf)return a ;
	data c ;
	c.total = a.total + b.total ;
	c.res = max(a.res, b.res) ;
	c.res = max(c.res, c.total) ;
	c.res = max(c.res, a.suffix + b.prefix) ;
	c.res = max(c.res, a.suffix + b.total) ;
	c.res = max(c.res, b.prefix + a.total) ;
	c.prefix = max(a.prefix, max(a.total + b.prefix, c.total)) ;
	c.suffix = max(b.suffix, max(b.total + a.suffix, c.total)) ;
	return c ;
}
 
void build(int i, int b, int e){
	if(b == e){
		T[i] = data(a[b], a[b], a[b], a[b]) ;
		return ;
	}
	int mid = (b + e) >> 1 ;
	build(i << 1, b, mid) ;
	build(i << 1 | 1, mid + 1, e) ;
	T[i] = merge(T[i << 1], T[i << 1 | 1]) ;
}
 
data query(int i, int b, int e, int l, int r){
	if(l > e or b > r)return data() ;
	if(l <= b and e <= r){
		return T[i] ;
	}
	int mid = (b + e) >> 1 ;
	data a = query(i << 1, b, mid, l, r) ;
	data d = query(i << 1 | 1, mid + 1, e, l, r) ;
	return merge(a, d) ;
}
 
int main() {
    // ios_base::sync_with_stdio(false) ;
    // cin.tie(NULL) ; cout.tie(NULL) ;
    int test = 1 , tc = 0 ;
    //Int(test) ;
    while (test--) {
        int n ; Int(n) ;
        for(int i = 1 ; i <= n ; ++i){
        	Int(a[i]) ;
        }
        build(1, 1, n) ;
        int q ; Int(q) ;
        while(q--){
        	int x, y ; Int(x, y) ;
        	data ans = query(1, 1, n, x, y) ;
        	printf("%d\n",ans.res);
        }
    }
    return 0 ;
}  
