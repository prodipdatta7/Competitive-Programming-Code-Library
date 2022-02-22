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
#define     mem(a)      memset(a , 0 ,sizeof a)
#define     memn(a)     memset(a , -1 ,sizeof a)
#define     filein      freopen("input.txt","r",stdin)
#define     fileout     freopen("output.txt","w",stdout)

inline int add(int a, int b, int mod){a += b ;return a >= mod ? a - mod : a ;}
inline int sub(int a, int b, int mod){a -= b ;return a < 0 ? a + mod : a ;}
inline int mul(int a, int b, int mod){return (ll)a * b % mod ;}

/*...Part - 06...*/
/*...... ! Code start from here ! ......*/

struct SuffixArray{
	int get(char c){
		if(c == '$')return 0 ;
		else if(c <= '9' and c >= '0')return c - '0' + 1 ;
		else if(c >= 'A' and c <= 'Z')return c - 'A' + 11 ;
		return c - 'a' + 37 ;
	}
	vi CyclicShift(string s){
		int n = sz(s) ;
		vi p(n), c(n), tmp(n), cnt(max(n, 68), 0) ;
		for(int i = 0 ; i < n ; ++i){
			++cnt[get(s[i])] ;
		}
		for(int i = 1 ; i < 65 ; ++i)
			cnt[i] += cnt[i - 1] ;
		for(int i = 0 ; i < n ; ++i)
			p[--cnt[get(s[i])]] = i ;
		c[p[0]] = 0 ;
		int sec = 1 ;
		for(int i = 1 ; i < n ; ++i){
			if(s[p[i]] != s[p[i - 1]])++sec ;
			c[p[i]] = sec - 1 ;
		}
		for(int h = 0 ; (1 << h) < n ; ++h){
			for(int i = 0 ; i < n ; ++i){
				tmp[i] = p[i] - (1 << h) ;
				if(tmp[i] < 0)tmp[i] += n ;
			}
			fill(cnt.begin(), cnt.begin() + sec, 0) ;
			for(int i = 0 ; i < n ; ++i)
				cnt[c[tmp[i]]]++ ;
			for(int i = 1 ; i < sec ; ++i)
				cnt[i] += cnt[i - 1] ;
			for(int i = n - 1 ; i >= 0 ; --i)
				p[--cnt[c[tmp[i]]]] = tmp[i] ;
			if(sec == n)return p ;
			tmp[p[0]] = 0 ;
			sec = 1 ;
			pii cur, prev ;
			for(int i = 1 ; i < n ; ++i){
				cur = {c[p[i]],c[(p[i] + (1 << h)) % n]} ;
				prev = {c[p[i - 1]],c[(p[i - 1] + (1 << h)) % n]} ;
				if(cur != prev)++sec ;
				tmp[p[i]] = sec - 1 ;
			}
			c.swap(tmp) ;
		}
		return p ;
	}

	void Construction(string s){
		s += '$' ;
		int n = sz(s) ;
		vi p = CyclicShift(s) ;
		for(int i = 1 ; i < n ; ++i)printf("%d\n",p[i]);
	}
} sa;

int main(){
    int test = 1 , tc = 0 ;
    while(test--){
        string s ; cin >> s ;
        sa.Construction(s) ;
    }
    return 0 ;
}

/*...Always look at the part - 04...*/
/*...............END................*/



