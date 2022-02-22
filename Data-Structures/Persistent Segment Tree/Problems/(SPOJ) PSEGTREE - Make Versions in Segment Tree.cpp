#include <bits/stdc++.h>
using namespace std ;

#define     debug(x, y)    cerr << #x << " = " << x << ' ' << #y << " = " << y << '\n' ;

struct DATA {
	DATA *left, *right ;
	int val ;
	DATA(int v = 0, DATA *a = NULL, DATA *b = NULL): val(v), left(a), right(b) {}

	void build(int b, int e, int arr[]) {
		if (b == e) {
			val = arr[b] ;
			return ;
		}
		left = new DATA() ;
		right = new DATA() ;
		int mid = (b + e) >> 1 ;
		left -> build(b, mid, arr) ;
		right -> build(mid + 1, e, arr) ;
		val = left -> val + right -> val ;
	}

	DATA* update(int b, int e, int pos, int v) {
		if (pos > e or b > pos)return this ;
		if (b == e) {
			DATA *ret = new DATA(val, left, right) ;
			ret -> val += v ;
			return ret ;
		}
		int mid = (b + e) >> 1 ;
		DATA *ret = new DATA(val) ;
		ret -> left = left -> update(b, mid, pos, v) ;
		ret -> right = right -> update(mid + 1, e, pos, v) ;
		ret -> val = ret -> left -> val + ret -> right -> val ;
		return ret ;
	}

	int query(int b, int e, int l, int r) {
		if (l > e or b > r)return 0 ;
		if (l <= b and e <= r)return val ;
		int mid = (b + e) >> 1 ;
		return left -> query(b, mid, l, r) + right -> query(mid + 1, e, l, r) ;
	}
} *root[100001] ;

int arr[100001] ;

int main() {
	int n ; scanf("%d", &n) ;
	for (int i = 1 ; i <= n ; ++i)
		scanf("%d", arr + i) ;
	root[0] = new DATA() ;
	root[0] -> build(1, n, arr) ;
	int ver = 0 ;
	int q ; scanf("%d", &q) ;
	while (q--) {
		int tp, pos, v, c ; scanf("%d %d %d %d", &tp, &pos, &v, &c) ;
		if (tp == 1) {
			root[++ver] = root[pos] -> update(1, n, v, c) ;
		}
		else {
			int sum = root[pos] -> query(1, n, v, c) ;
			cout << sum << '\n' ;
		}
	}
}
