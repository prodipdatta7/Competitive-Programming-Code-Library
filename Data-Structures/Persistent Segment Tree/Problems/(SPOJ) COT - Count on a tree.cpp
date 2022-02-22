#include <bits/stdc++.h>
using namespace std ;

const int N = (int)1e5 + 5 ;

int w[N], org[N], dep[N], par[N][18] ;
int n, m ;
vector < vector < int > > g ;

struct node {
	int val ;
	node *left, *right ;
	node(int v = 0, node *l = nullptr, node *r = nullptr): val(v), left(l), right(r) {}

	void build(int b, int e) {
		if (b == e)return ;
		left = new node() ;
		right = new node() ;
		int mid = (b + e) >> 1 ;
		left -> build(b, mid) ;
		right -> build(mid + 1, e) ;
	}

	node* update(int b, int e, int pos) {
		if (b > pos or e < pos)return this ;
		if (b == e) {
			node* cur = new node(val, left, right) ;
			cur -> val++ ;
			return cur ;
		}
		int mid = (b + e) >> 1 ;
		node* cur = new node(val) ;
		cur -> left = left -> update(b, mid, pos) ;
		cur -> right = right -> update(mid + 1, e, pos) ;
		cur -> val = cur -> left -> val + cur -> right -> val ;
		return cur ;
	}
}*root[N] ;

void dfs(int s, int p = 0) {
	dep[s] = 1 + dep[p] ;
	par[s][0] = p ;
	root[s] = root[p] -> update(1, n, w[s]) ;
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
			a = par[a][i], b = par[b][i] ;
		}
	}
	return par[a][0] ;
}

int query(node* u, node* c, node* v, node* d, int b, int e, int k) {
	if (b == e)return b ;
	int cnt = u -> left -> val - c -> left -> val + v -> left -> val - d -> left -> val ;
	int mid = (b + e) >> 1 ;
	if (cnt >= k)return query(u -> left, c -> left, v -> left, d -> left, b, mid, k) ;
	else return query(u -> right, c -> right, v -> right, d -> right, mid + 1, e, k - cnt) ;
}

int main() {

	scanf("%d %d", &n, &m) ;
	vector < int > tmp ;
	g.resize(n + 1) ;

	for (int i = 1 ; i <= n ; ++i) {
		scanf("%d", &w[i]) ;
		tmp.push_back(w[i]) ;
	}
	sort(tmp.begin(), tmp.end()) ;
	for (int i = 1 ; i <= n ; ++i) {
		int c = lower_bound(tmp.begin(), tmp.end(), w[i]) - tmp.begin() + 1 ;
		org[c] = w[i] ;
		w[i] = c ;
	}
	// for(int i = 1 ; i <= n ; ++i){
	// 	cout << w[i] << '\n' ;
	// }
	for (int i = 1 ; i < n ; ++i) {
		int x, y ;
		scanf("%d %d", &x, &y) ;
		g[x].push_back(y) ;
		g[y].push_back(x) ;
	}
	root[0] = new node() ;
	root[0] -> build(1, n) ;
	dfs(1) ;
	while (m--) {
		int u, v, k ; scanf("%d %d %d", &u, &v, &k) ;
		int up = lca(u, v) ;
		//cout << "lca = " << up << '\n' ;
		int res = query(root[u], root[up], root[v], root[par[up][0]], 1, n, k) ;
		//cout << "res = " << res << '\n' ;
		printf("%d\n", org[res]);
	}
}
