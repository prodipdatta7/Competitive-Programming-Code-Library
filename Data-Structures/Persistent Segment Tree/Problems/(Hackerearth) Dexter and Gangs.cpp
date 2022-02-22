
/* max frequent weight on the path u -> v */

/* alternate solution: Find the median value of the path and then get the frequency of the median */

#include <bits/stdc++.h>
using namespace std ;

const int N = (int)1e5 + 5;

int L[20 * N], R[20 * N], T[20 * N], root[N], a[N], idx, n, m ;
int dep[N], par[N][18] ;
vector < vector < int > > g ;

void build(int i, int b, int e) {
	//cout << "b = " << b << " e = " << e << '\n' ;
	if (b == e)return ;
	int mid = (b + e) >> 1 ;
	L[i] = ++idx ;
	R[i] = ++idx ;
	build(L[i], b, mid) ;
	build(R[i], mid + 1, e) ;
}

int update(int i, int b, int e, int pos) {
	if (pos > e or b > pos)return i ;
	int k = ++idx ;
	if (b == e) {
		T[k] = 1 + T[i] ;
		return k ;
	}
	int mid = (b + e) >> 1 ;
	L[k] = update(L[i], b, mid, pos) ;
	R[k] = update(R[i], mid + 1, e, pos) ;
	T[k] = T[L[k]] + T[R[k]] ;
	return k ;
}

int query(int i, int j, int k, int l, int b, int e, int half) {
	if (b == e)return b ;
	int mid = (b + e) >> 1 ;
	int sum = T[L[i]] + T[L[j]] - T[L[k]] - T[L[l]] ;
	int sum1 = T[R[i]] + T[R[j]] - T[R[k]] - T[R[l]] ;
	if (sum > half)return query(L[i], L[j], L[k], L[l], b, mid, half) ;
	else if (sum1 > half)return query(R[i], R[j], R[k], R[l], mid + 1, e, half) ;
	return -1 ;
}

void dfs(int s, int p = 0) {
	//cout << "s = " << s << " p = " << p << '\n' ;
	dep[s] = 1 + dep[p] ;
	par[s][0] = p ;
	root[s] = update(root[p], 1, n, a[s]) ;
	for (int i = 1 ; i < 18 ; ++i)
		par[s][i] = par[par[s][i - 1]][i - 1] ;
	for (int i : g[s]) {
		if (i == p)continue ;
		dfs(i, s) ;
	}
}

int lca(int a, int b) {
	if (dep[a] < dep[b])swap(a, b) ;
	int d = dep[a] - dep[b] ;
	for (int i = 17 ; i >= 0 ; --i) {
		if (d & (1 << i))a = par[a][i] ;
	}
	if (a == b)return a ;
	for (int i = 17 ; i >= 0 ; --i) {
		if (par[a][i] != par[b][i]) {
			a = par[a][i] ;
			b = par[b][i] ;
		}
	}
	return par[a][0] ;
}

int main() {
	scanf("%d%d", &n, &m) ;
	vector < int > box, rev(n + 1) ;
	for (int i = 1 ; i <= n ; ++i) {
		scanf("%d", &a[i]) ;
		box.push_back(a[i]) ;
	}
	sort(box.begin(), box.end()) ;
	for (int i = 1 ; i <= n ; ++i) {
		int x = lower_bound(box.begin(), box.end(), a[i]) - box.begin() + 1 ;
		rev[x] = a[i] ;
		a[i] = x ;
	}
	g.resize(n + 1) ;
	for (int i = 1 ; i < n ; ++i) {
		int x, y ; scanf("%d%d", &x, &y) ;
		g[x].push_back(y) ;
		g[y].push_back(x) ;
	}
	root[0] = 0 ;
	idx = 0 ;
	build(0, 1, n) ;
	dfs(1) ;
	while (m--) {
		int u, v ; scanf("%d%d", &u, &v) ;
		int mid = lca(u, v) ;
		int cnt = dep[u] + dep[v] - dep[mid] - dep[par[mid][0]] ;
		//cout << "lca = " << mid << " cnt = " << cnt << '\n' ;
		int res = query(root[u], root[v], root[mid], root[par[mid][0]], 1, n, cnt / 2) ;
		if (res == -1)puts("S") ;
		else cout << "D " << rev[res] << '\n' ;
	}
}
