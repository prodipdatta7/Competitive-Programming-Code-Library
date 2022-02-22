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
 
int Int(){int x ; scanf("%d",&x) ; return x ;}
ll Long(){ll x ; scanf("%lld",&x) ; return x ;}
 
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
#define		fileIn		freopen("in.txt","r",stdin)
#define		fileOut		freopen("out.txt","w",stdout)
 
/*...Part - 06...*/
/*...... ! Code start from here ! ......*/
 
int p[N] ;
 
string preProcess(string s){
	if(sz(s) == 0)return "^$" ;
	int n = sz(s) ;
	string res = "^" ;
	for(int i = 0 ; i < n ; ++i){
		res += "#" + s.substr(i , 1) ;
	}
	res += "#$" ;
	return res ;
}
 
int manacher(string s){
	string T = preProcess(s) ;
	int n = sz(T) ;
	int c = 0 , r = 0 ; 
	mem(p) ;
	int a = 0 , b = 0 ;
	for(int i = 1 ; i < n - 1 ; ++i){
		int mirror = (c << 1) - i ;
		p[i] = (i < r) ? min(p[mirror] , r - i) : 0 ;
		while(T[i + 1 + p[i]] == T[i - 1 - p[i]])++p[i] ;
		if(i + p[i] > r){
			r = i + p[i] ;
			c = i ;
		}
		if(p[i] > a){
			a = p[i] ;
			b = 1 ;
		}
		else if(p[i] == a){
			++b ;
		}
	}
	printf("%d %d\n",a , b);
	return 0 ;
}
 
int main(){
    int test = Int , tc = 0 ;
    while(test--){
        string s ; cin >> s ;
        manacher(s) ;
    }
    return 0 ;
}
 
/*...Always look at the part - 04...*/
/*...............END................*/
