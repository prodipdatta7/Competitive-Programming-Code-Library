#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5 ;
const double eps = 1e-9 ;
const int MAX_N = 1e6 + 5 ;
const int inf = 2e9 ; 
const long long Inf = (long long)1e18 ;
const long long M = (long long)1e9+7 ;
#define     ll      long long
#define     ull     unsigned long long
#define        ignore    continue
#define        exit    break
int Int() {
    int x;
    scanf("%d",&x);
    return x;
}
ll Long() {
    ll x;
    scanf("%lld",&x);
    return x;
}
void Char(char* ch) {
    scanf("%s",ch);
}
template<typename t>inline t abs(t a) { if(a>=0) return a; return -a;}
template<typename t>inline t gcd(t a , t b) {return !b ? a : gcd(b , a % b);}
template<typename t>inline t lcm(t a , t b) {return a * ( b /gcd(a , b));}
template<typename T>inline T modpow(T b, T p, T Mod) {
    T res  = 1;
    while(p > 0) {
        if(p&1) {
            res *= b ;
            res %= Mod ;
        }
        b *= b;
        b %= Mod;
        p >>= 1;
    }
    return res ;
}

template<typename T> inline T ModInv(T b, T Mod) {return modpow(b, Mod - 2, Mod );}

template<typename T> inline T pwr(T b, T p) {
    T res  = 1;
    while(p > 0) {
        if(p&1) {
            res *= b ;
        }
        b *= b;
        p >>= 1;
    }
    return res ;
}
int e1 , e2 , d1 ;
template < typename T >inline void extgcd(T a , T b){
    if(!b) {e1 = 1 , e2 = 0 , d1 = a ; return ;}
    extgcd(b , a % b) ;
    T x1 = e2 ; 
    T y1 = e1 - (a / b) * e2 ;
    e1 = x1 ;
    e2 = y1 ;
}

/*primes in range 1 - n
1 - 100(1e2) -> 25 pimes
1 - 1000(1e3) -> 168 primes
1 - 10000(1e4) -> 1229 primes
1 - 100000(1e5) -> 9592 primes
1 - 1000000(1e6) -> 78498 primes
1 - 10000000(1e7) -> 664579 primes
large primes -> 
104729 1299709 15485863 179424673 2147483647 32416190071 112272535095293 48112959837082048697
*/
/*
PRIMES vs Range
100(1e2) primes -> 541 (5e2 + 41)
1000(1e3) primes -> 7919(7e3 + 9e2 + 19)
10000(1e4) primes -> 104729(1e5 + 4e3 + 7e2 + 29)
100000(1e5) primes -> 1299709(1e6 + 2e5 + 9e4 + 9e3 + 7e2 + 9)
1000000(1e6) primes -> 15485863(1e7 + 5e6 + 4e5 + 8e4 + 5e3 + 8e2 + 63)
*/
/*
std::vector<int> primes;
bitset < MAX_N > bs;
ll sieve_size = MAX_N ;

void sieve(ll n){
    bs.set() ;
    int cnt = 0 ;
    bs[0] = bs[1] = 0 ;
    for(ll i = 2 ; i <= n ; i++)if(bs[i]){
        primes.push_back((int)i);
        for(ll j = i * i ; j <= n ; j += i) bs[j] = 0;
    }
}
*/
// LINEAR SIEVE -> O(N) COMPLEXITY

bool is_composite[MAX_N] ;
std::vector< int > pm;

void linear_sieve(){
    for(int i = 2 ; i < MAX_N ; i++){
        if(!is_composite[i])pm.push_back(i) ;
        for(int j = 0 ; j < (int)pm.size() and i * pm[j] < MAX_N ; j++){
            is_composite[i * pm[j]] = 1 ;
            if(i % pm[j] == 0)break ;
        }
    }
}
/*
bool isprime(ll n){
    if(n <= sieve_size)return bs[n] ;
    for(int i = 0 ; i < (int)primes.size() ; i++){
        if(n % primes[i] == 0)return false ;
    }
    return true ;
}

int numDiffPf[MAX_N] ;

void DiffPF(){
    for(int i = 2 ; i < MAX_N ; i++){
        if(numDiffPf[i] == 0){
            for(int j = i ; j < MAX_N ; j += i)numDiffPf[j]++;
        }
    }
}
//Minimum Prime Factor

std::vector< int > factor;
void minFactor(ll n){
    factor.assign((int)n + 1 , 0) ;
    for(ll i = 2 ; i <= n ; i++){
        if(factor[i] != 0) continue ;
        for(ll j = i * i ; j <= n ; j += i){
            if(factor[j] == 0)factor[j] = i ;
        }
    }
}

int Phi[MAX_N] ;

void EulerPHI(){
    for(int i = 1 ; i < MAX_N ; i++)Phi[i] = i ;
        for(int i = 2 ; i < MAX_N ; i++)
            if(Phi[i] == i)
                for(int j = i ; j < MAX_N ; j += i)
                    Phi[j] = (Phi[j]/i) * (i - 1) ;
}

int F(int x){
    return 0 ;
}
pair < int , int > floydCycle(int x0){
    int tor = F(x0) , hare = F(F(x0)) ;
    while(tor != hare){tor = F(tor) , hare = F(F(hare));}
    int mu = 0 ; hare = x0 ;
    while(tor != hare){tor = F(tor) , hare = F(hare); mu++ ;}
    int lambda = 1 ; hare = F(tor) ;
    while(tor != hare){hare = F(hare) ; lambda++;}
    return {mu , lambda} ;
}
*/
template <typename T>inline vector< T > Unique(vector< T > v) {
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()),v.end());
    return v;
}
#define rep(i, begin, end) for (__typeof(end) i = (begin) ; i != (end) + 1 - 2 * ((begin) > (end)) ; i += 1 - 2 * ((begin) > (end)))
///error///
#define error(args...) {vector<string>_v=split(#args,',');err(_v.begin(),args);cout<<endl;}
vector<string> split(const string &s,char c) {
    vector<string>v;
    stringstream ss(s);
    string x;
    while(getline(ss,x,c))
        v.emplace_back(x);
    return move(v);
}

void err(vector<string>::iterator it) {}
template<typename T,typename... Args>
void err(vector<string>::iterator it,T a,Args...args) {
    cout<<it->substr((*it)[0]==' ',it->length())<< " = " << a << " ";
    err(++it,args...);
}
///This DEBUGGER-tool need c++11///
#define     Int                 Int()
#define     Long                Long()
#define     pii                 pair<int,int>
#define     ff                  first
#define     ss                  second
#define     pb                  push_back
#define     eb                  emplace_back
#define     all(x)              x.begin(),x.end()
#define     mem(a)              memset(a,0,sizeof a)
#define     memn(a)             memset(a,-1,sizeof a)

std::vector< ll > dv;
std::vector< ll > sum;

ll calPhi(ll n){
	ll res = n ;
	for(int i = 0 ; 1LL * pm[i] * pm[i] <= n ; i++){
		if((n % pm[i]) == 0){
			res /= pm[i] ;
			res *= (pm[i] - 1) ;
			while(n % pm[i] == 0)n /= pm[i] ;
		}
	}
	if(n > 1)res /= n , res *= (n - 1) ;
	return res ;
}

int main() {
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    linear_sieve() ;
    int t = Int , tc = 0 ;
    while(t--) {
       	ll n = Long , q = Int ;
       	sum.clear() ;
       	dv.clear() ;
       	for(ll i = 1 ; i * i <= n ; i++){
       		if(n % i == 0){
       			dv.pb(i) ;
       			if(n / i != i)dv.pb(n / i) ;
       		}
       	}
       	sort(all(dv)) ;
       	int sz = (int)dv.size() ;
       	sum.resize(sz + 1 , 0) ;
       	for(int i = 0 ; i < sz ; i++){
       		sum[i] = calPhi(n / dv[i]) ;
       		if(i)sum[i] += sum[i - 1] ;
       	}
       	printf("Case %d\n",++tc);
       	while(q--){
       		ll k = Long ;
       		if(k > n)printf("%lld\n",sum[sz - 1]);
       		else if(k < 1)printf("0\n");
       		else{
       			int pos = upper_bound(all(dv) , k) - dv.begin() ;
       			pos-- ;
       			printf("%lld\n",sum[pos]);
       		}
       	}
    }
    return 0;
}

