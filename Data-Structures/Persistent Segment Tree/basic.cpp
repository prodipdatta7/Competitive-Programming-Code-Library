int L[maxN], R[maxN], T[maxN], root[N], idx, a[N], n ;

void build(int i, int b, int e){
	if(b == e)return ;
	int mid = (b + e) >> 1 ;
	L[i] = ++idx ; 
	R[i] = ++idx ;
	build(L[i], b, mid) ;
	build(R[i], mid + 1, e) ;
}

int update(int i, int b, int e, int pos, int v){
	if(pos < b or e < pos)return i ;
	int id = ++idx ;
	if(b == e){
		T[id] = T[i] + v ;
		return id ;
	}
	int mid = (b + e) >> 1 ;
	L[id] = update(L[i], b, mid, pos, v) ;
	R[id] = update(R[i], mid + 1, e, pos, v) ;
	T[id] = T[L[id]] + T[R[id]] ;
	return id ;
}

int Kth(int i, int b, int e, int k){
	if(b == e) return T[i] == k ? b : n + 1 ;
	int mid = (b + e) >> 1 ;
	if(T[L[i]] >= k)return Kth(L[i], b, mid, k) ;
	else return Kth(R[i], mid + 1, e, k - T[L[i]]) ;
}
