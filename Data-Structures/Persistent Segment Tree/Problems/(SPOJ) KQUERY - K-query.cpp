#include <bits/stdc++.h>
using namespace std ;

const int N = (int)2e6 + 5 ;

int L[N], R[N], T[N] ;
int version, root[30004] ;

void build(int i, int b, int e) {
    if (b == e) {
        T[i] = 0 ;
        return ;
    }
    int mid = (b + e) >> 1 ;
    L[i] = ++version ;
    R[i] = ++version ;
    build(L[i], b, mid) ;
    build(R[i], mid + 1, e) ;
}

int update(int i, int b, int e, int pos) {
    if (b > pos or e < pos)return i ;
    int k = ++version ;
    if (b == e) {
        T[k] = T[i] + 1 ;
        return k ;
    }
    int mid = (b + e) >> 1 ;
    L[k] = update(L[i], b, mid, pos) ;
    R[k] = update(R[i], mid + 1, e, pos) ;
    T[k] = T[L[k]] + T[R[k]] ;
    return k ;
}

int query(int i, int b, int e, int l, int r) {
    if (r < b or e < l)return 0 ;
    if (l <= b and e <= r)return T[i] ;
    int mid = (b + e) >> 1 ;
    return query(L[i], b, mid, l, r) + query(R[i], mid + 1, e, l, r) ;
}

int main() {
    int n ; scanf("%d", &n) ;
    root[0] = 0 ;
    vector < int > a(n + 1), b ;
    for (int i = 1 ; i <= n ; ++i) {
        int x ; scanf("%d", &x) ;
        b.push_back(x);
        a[i] = x ;
    }
    int q ; scanf("%d", &q) ;
    vector < pair < pair < int, int > , int > > Q ;
    for (int i = 1 ; i <= q ; ++i) {
        int l, r, k ; scanf("%d %d %d", &l, &r, &k) ;
        Q.push_back(make_pair(make_pair(l, r), k)) ;
        b.push_back(k) ;
    }
    unordered_map< int, int > cmp ;
    sort(b.begin(), b.end()) ;
    int cnt = 0 ;
    for (int i = 0 ; i < n + q ; ++i) {
        if (!cmp[b[i]])cmp[b[i]] = ++cnt ;
    }
    version = 0 ;
    build(0, 1, cnt) ;
    for (int i = 1 ; i <= n ; ++i) {
        a[i] = cmp[a[i]] ;
        root[i] = update(root[i - 1], 1, cnt, a[i]) ;
    }
    for (int i = 0 ; i < q ; ++i) {
        int l = Q[i].first.first, r = Q[i].first.second, k = Q[i].second ;
        k = cmp[k] ;
        int res = query(root[r], 1, cnt, k + 1, cnt) - query(root[l - 1], 1, cnt, k + 1, cnt) ;
        printf("%d\n", res);
    }
    return 0 ;
}
