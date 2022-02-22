#include <bits/stdc++.h>
using namespace std ;

const int N = (int)2e6 + 5 ;

int L[N] ;
int R[N] ;
int T[N] ;
int version ;
int root[N] ;
int src[N] ;
int pos[N] ;

void build(int i, int b, int e) {
    if (b == e) {
        T[i] = 0 ;
        return ;
    }
    L[i] = ++version ;
    R[i] = ++version ;
    int mid = (b + e) >> 1 ;
    build(L[i], b, mid) ;
    build(R[i], mid + 1, e) ;
}

int update(int i, int b, int e, int pos) {
    if (b > pos or e < pos)return i ;
    int cur = ++version ;
    if (b == e) {
        T[cur] = T[i] + 1 ;
        return cur ;
    }
    int mid = (b + e) >> 1 ;
    L[cur] = update(L[i], b, mid, pos) ;
    R[cur] = update(R[i], mid + 1, e, pos) ;
    T[cur] = T[L[cur]] + T[R[cur]] ;
    return cur ;
}

int query(int i, int j, int b, int e, int l) {
    if (b >= l)return 0 ;
    if (e < l)return T[i] - T[j] ;
    int mid = (b + e) >> 1 ;
    return query(L[i], L[j], b, mid, l) + query(R[i], R[j], mid + 1, e, l) ;
}

int main() {
    //cout << N * 4 * LogN<< '\n' ;
    int test = 1, tc = 0;
    scanf("%d", &test) ;
    while (test--) {
        int n, q ; scanf("%d%d", &n, &q) ;
        memset(L, 0, sizeof L) ;
        memset(R, 0, sizeof R) ;
        memset(T, 0, sizeof T) ;
        memset(root, 0, sizeof root) ;
        memset(pos, 0, sizeof pos) ;
        version = 0 ;
        int cnt = 0 ;
        root[0] = 0 ;
        build(0, 0, n) ;
        for (int i = 1 ; i <= n ; ++i) {
            int x ; scanf("%d", &x) ;
            int k = pos[x] ;
            root[i] = update(root[i - 1], 0, n, k) ;
            pos[x] = i ;
        }
        printf("Case %d:\n", ++tc);
        while (q--) {
            int l, r ; scanf("%d %d", &l, &r) ;
            int res = query(root[r], root[l - 1], 0, n, l) ;
            printf("%d\n", res);
        }
    }
    return 0 ;
}
