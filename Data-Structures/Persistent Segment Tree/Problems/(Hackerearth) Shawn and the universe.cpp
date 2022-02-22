/* First missing number(starting from 1) in the range (L, R) strictly greater than k*/

#include <bits/stdc++.h>
using namespace std ;

const int N = (int)1e6 + 6 ;

int L[5 * N], R[5 * N], T[5 * N], TT[5 * N], root[N], idx ;

void build(int i, int b, int e, int k){
	if(b == e){
		T[i] = b > k ;
		TT[i] = 0 ;
		return ;
	}
	L[i] = ++idx ;
	R[i] = ++idx ;
	int mid = (b + e) >> 1 ;
	build(L[i], b, mid, k) ;
	build(R[i], mid + 1, e, k) ;
	T[i] = T[L[i]] + T[R[i]] ;
}

int update(int i, int b, int e, int pos, int up){
	if(b > pos or e < pos)return i ;
	int k = ++idx ;
	if(b == e){
		T[k] = 0 ;
		TT[k] = b > up ;
		return k ; 
	}
	int mid = (b + e) >> 1 ;
	L[k] = update(L[i], b, mid, pos, up) ;
	R[k] = update(R[i], mid + 1, e, pos, up) ;
	T[k] = T[L[k]] + T[R[k]] ;
	TT[k] = TT[L[k]] + TT[R[k]] ;
	return k ;
}

int query(int i, int j, int b, int e){
	if(b == e)return b ;
	int mid = (b + e) >> 1 ;
	int cnt = T[L[i]] + TT[L[j]] ;
	if(cnt)return query(L[i], L[j], b, mid) ;
	else return query(R[i], R[j], mid + 1, e) ;
}

int main(){
	int n, k ; scanf("%d %d",&n, &k) ;
	idx = 0 ;
	root[0] = 0 ;
	build(0, 1, N - 1, k) ;
	for(int i = 1 ; i <= n ; ++i){
		int x ; scanf("%d",&x) ;
		root[i] = update(root[i - 1], 1, N - 1, x, k) ;
	}
	int q ; scanf("%d",&q) ;
	while(q--){
		int l, r ; scanf("%d %d",&l, &r) ;
		int res = query(root[r], root[l - 1], 1, N - 1) ;
		printf("%d\n",res);
	}
}
