#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define si(X) scanf("%d", &(X))
#define sll(X) scanf("%lld",&(X))
#define INFL 0x3f3f3f3f3f3f3f3fLL
ll gcd(ll a,ll b){
	if(b==0)
	return a;
	return gcd(b,a%b);
}
string toBin(ll a) {
	string res = "";
	while (a) {
		res += char((a & 1) + '0');
		a >>= 1;
	}
	reverse(res.begin(), res.end());
	return res;
}
const int mod = 1e9+7;
ll expo(ll base,ll pow){
    ll ans = 1;
    while(pow!=0){
        if(pow&1==1){
            ans = ans*base;
            ans = ans%mod;
        }
        base *= base;
        base%=mod;
        pow/=2;
    }
    return ans;
}
ll inv(ll x){
    return expo(x,mod-2);
}
bool isPal(string ss){
    int len = ss.length();
    for(int i = 0 ; i<len/2 ; i++){
	int comp = len-i-1;
	if(ss[i]!=ss[comp])
		return false;
	}
    return true;
}
double pi = 3.141592653589793238462643;
double error = 0.0000001;
/* -------Template ends here-------- */
 
const int M = 1e5 + 5;
 
vector<int> vec[M];
bool vis[M];
int disc[M] , lo[M] , comp[M] , cc[M];
int tim = 1;
int par[M];
int ar[M];
set<pair<int , int> > se;
int nodesInComp[M];
 
void findBridges(int u){
    vis[u] = 1;
    lo[u] = disc[u] = tim++;
    for(int i = 0 ; i<vec[u].size() ; i++){
        int v = vec[u][i];
        if(vis[v]){
            if(v != par[u])
                lo[u] = min(lo[u] , disc[v]);
        }
        else{
            par[v] = u;
            findBridges(v);
            lo[u] = min(lo[u] , lo[v]);
            if(lo[v] > disc[u]){
                se.insert(make_pair(u , v));
            }
        }
    }
}
int till = 1;
int has = 0;
 
void divideGraphInComps(int u){
    comp[u] = till;
    nodesInComp[comp[u]]++;
    vis[u] = 1;
    for(int i = 0 ; i<vec[u].size()  ;i++){
        int v = vec[u][i];
        if(vis[v]) continue;
        if(se.count(make_pair(u , v)) || se.count(make_pair(v , u))) continue;
        divideGraphInComps(v);
    }
}
vector<int> vv[M];
 
int dis = 0 , ind = 1;
 
void createBlockCutTree(int u){
    vis[u] = 1;
    for(int i = 0 ; i<vec[u].size() ; i++){
        int v = vec[u][i];
        if(vis[v]) continue;
        if(comp[u] != comp[v]){
            vv[comp[u]].push_back(comp[v]);
            vv[comp[v]].push_back(comp[u]);
        }
        createBlockCutTree(v);
    }
}
//vector<int> ss;
void rock(int u , int dd){
    if(dd > dis){
        dis = dd;
        ind = u;
    }
    vis[u] = 1;
    for(int i = 0 ; i<vv[u].size() ; i++){
        int v = vv[u][i];
        if(vis[v]) continue;
      //  cout<<"rr "<<u<<"   "<<v<<endl;
        rock(v , dd + 1);
    }
}
 
int goodBridges = 0;
int subtree[M];
int n;
void dfsOnTree(int u){
    vis[u] = 1;
    subtree[u] = nodesInComp[u];
 
    for(int i = 0 ; i < vv[u].size() ; i++){
        int v = vv[u][i];
        if(vis[v]) continue;
        dfsOnTree(v);
        subtree[u] += subtree[v];
    }
 
    if(subtree[u] == 0 || subtree[u] == n) return;
    if((n - subtree[u])%2 == 0 && (subtree[u]%2) == 0){
        goodBridges++;
    }
 
}
ll findAns(int a, int b){
    int g = gcd(a, b);
    a /= g;
    b /= g;
    ll ans = a*1LL*(inv(b));
    ans %= mod;
    return ans;
}

int main(){
    
    int e;
    si(n);  si(e);
 
    for(int i = 0 ; i < e ; i++){
        int u , v;
        si(u);  si(v);
        vec[u].push_back(v);
        vec[v].push_back(u);
    }

    memset(vis , 0 , sizeof(vis));
 
    for(int i = 1 ; i <= n ; i++){
        if(vis[i] == 0) findBridges(i);
    }
 
    memset(vis , 0 , sizeof(vis));
 
    for(int i = 1 ; i<=n ; i++){
        if(vis[i]) continue;
        divideGraphInComps(i);
        till++;
    }
 
    memset(vis , 0 , sizeof(vis));
 
    for(int i = 1 ; i <= n ; i++){
        if(vis[i]) continue;
        createBlockCutTree(i);
    }
 
    memset(vis , 0 , sizeof(vis));
    dis = 0;
    ind = 1;
 
    int times = 0;
    for(int i = 1 ; i < till ; i++){
        if(vis[i] == 0){
            times++;
            dfsOnTree(i);
        }
    }
    int totBridges = se.size();
    if(times > 1 || totBridges == 0){
        cout<<"0 0";
        return 0;
    }
    
    ll Aans = findAns(goodBridges, totBridges);
    ll BAns = findAns(totBridges - goodBridges, totBridges);
 
 
    cout<<Aans<<" "<<BAns;
 
}
 
