#include <bits/stdc++.h>
 
using namespace std;
#define ll long long
#define ull unsigned long long
#define si(X) scanf("%d", &(X))
#define sll(X) scanf("%lld",&(X))
#define INFL 0x3f3f3f3f3f3f3f3fLL
const int mod = 1e9 + 7;
ll gcd(ll a, ll b) { if (b == 0)return a; return gcd(b, a%b); }
ll expo(ll base, ll pow) {
	ll ans = 1;
	while (pow != 0) {
		if (pow & 1 == 1) { ans = ans * base; ans = ans % mod; }
		base *= base; base %= mod; pow /= 2;
	}return ans;
}
ll inv(ll x) { return expo(x, mod - 2); }
double pi = 3.141592653589793238462643;
double error = 0.0000001;
int dx[8] = { 1 , 0 , -1 , 0 , 1 , -1 , -1 , 1 };    // last 4 diagonal
int dy[8] = { 0 , 1 , 0 , -1 , 1 , 1 , -1 , -1 };
/*------------------------------------------------------------------------------------*/
 
const int M = 1e5 + 5;
 
ll arr[M];
struct Node {
	int lef, rig;
};
 
// maximum node we need for a trie with M number each with depth 32
Node node[32 * M];
int numOfNodeUsed = 0;
 
int getNew() {
	int cur = numOfNodeUsed++;
	node[cur].lef = -1;
	node[cur].rig = -1;
	return cur;
}
 
void ins(ll num, int root) {
	int temp = root;
	for (int j = 30; j >= 0; j--) {
		if ((1LL << j)&num) {
			if (node[temp].rig == -1) {
				node[temp].rig = getNew();
			}
			temp = node[temp].rig;
		}
		else {
			if (node[temp].lef == -1) {
				node[temp].lef = getNew();
			}
			temp = node[temp].lef;
		}
	}
}
 
ll min_xor(ll num, int root) {
	int temp = root;
	ll ans = 0;
 
	for (int j = 30; j >= 0; j--) {
		bool onlef = (((1LL << j)&num) == 0);
 
		if (temp == -1 || (node[temp].lef == -1 && node[temp].rig == -1)) {
			ans += (1LL << j);
			break;
		}
 
		if (onlef && node[temp].lef != -1) {
			temp = node[temp].lef;
		}
		else if (!onlef && node[temp].rig != -1) {
			temp = node[temp].rig;
		}
 
		else if (onlef) {
			ans += (1LL << j);
			temp = node[temp].rig;
		}
		else if (!onlef) {
			ans += (1LL << j);
			temp = node[temp].lef;
		}
	}
 
	return ans;
 
}
 
int main() {
 
	int t;
	si(t);
 
	while (t--) {
 
		// free all node
		numOfNodeUsed = 0;
 
		int n;
		si(n);
 
		for (int i = 1; i <= n; i++) {
			sll(arr[i]);
		}

		int rootA = getNew();
 
		ins(arr[1], rootA);
		ll ans = 1000 * 1LL * mod;
		bool ok = 0;
		for (int i = 2; i <= n; i++) {
			ans = min(ans, min_xor(arr[i], rootA));
			if (ans == 0) {
				ok = 1;
				break;
			}
			ins(arr[i], rootA);
		}
		if (ok) {
			cout << "0" << endl;
			continue;
		}
		cout << ans << endl;;
	}
}