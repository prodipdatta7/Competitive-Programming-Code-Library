#include <bits/stdc++.h>
using namespace std ;

struct node {
	int val ;
	node *left, *right ;
	node(int v = 0, node *l = NULL, node *r = NULL): val(v), left(l), right(r) {}

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
			node* ret = new node(val, left, right) ;
			ret -> val++ ;
			return ret ;
		}
		int mid = (b + e) >> 1 ;
		node *ret = new node(val) ;
		ret -> left = left -> update(b, mid, pos) ;
		ret -> right = right -> update(mid + 1, e, pos) ;
		ret -> val = ret -> left -> val + ret -> right -> val ;
		return ret ;
	}

} *root[100005] ;


int query(node* a, node* b, int l, int r, int k) {
	if (l == r)return l ;
	int L = a -> left -> val - b -> left -> val ;
	int mid = (l + r) >> 1 ;
	if (L >= k)return query(a -> left, b -> left, l, mid, k) ;
	else return query(a -> right, b -> right, mid + 1, r, k - L) ;
}

int main() {
	int n, q; scanf("%d %d", &n, &q) ;
	root[0] = new node() ;
	root[0] -> build(1, n) ;
	vector < int > val, mp, rev(n + 1, 0) ;
	for (int i = 1 ; i <= n ; ++i) {
		int x ; scanf("%d", &x) ;
		val.push_back(x) ;
		mp.push_back(x) ;
		//root[i] = root[i - 1] -> update(1, n, x) ;
	}
	sort(mp.begin(), mp.end()) ;
	int p = 1 ;
	for (int &i : val) {
		int c = lower_bound(mp.begin(), mp.end(), i) - mp.begin() + 1 ;
		rev[c] = i ;
		root[p] = root[p - 1] -> update(1, n, c) ;
		++p ;
		//cout << "i = " << i << '\n' ;
	}
	while (q--) {
		int l, r, k ; scanf("%d %d %d", &l, &r, &k) ;
		int res = query(root[r], root[l - 1], 1, n, k) ;
		printf("%d\n", rev[res]);
	}

}
