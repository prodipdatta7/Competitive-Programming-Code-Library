template <typename type> struct SparseTable {
    int n ;
    vector < vector < type > > T ;
    vector < int > logTable ;
    SparseTable(int _n = 0) : n(_n) {
        logTable.assign(n + 1, 0) ;
        logTable[1] = 0 ;
        for (int i = 2 ; i <= n ; ++i)
            logTable[i] = logTable[i >> 1] + 1 ;
        T.assign(n + 1, vector < type > (logTable[n] + 1)) ;
    }
    inline void build_max(vector < type > &a) {
        for (int i = 1 ; i <= n ; ++i) {
            T[i][0] = a[i] ;
        }
        for (int j = 1 ; (1 << j) <= n ; ++j) {
            for (int i = 1 ; i + (1 << j) - 1 <= n ; ++i) {
                T[i][j] = max(T[i][j - 1], T[i + (1 << (j - 1))][j - 1]) ;
            }
        }
    }
    inline void build_min(vector < type > &a) {
        for (int i = 1 ; i <= n ; ++i) {
            T[i][0] = a[i] ;
        }
        for (int j = 1 ; (1 << j) <= n ; ++j) {
            for (int i = 1 ; i + (1 << j) - 1 <= n ; ++i) {
                T[i][j] = min(T[i][j - 1], T[i + (1 << (j - 1))][j - 1]) ;
            }
        }
    }
    inline void build_gcd(vector < type > &a) {
        for (int i = 1 ; i <= n ; ++i) {
            T[i][0] = a[i] ;
        }
        for (int j = 1 ; (1 << j) <= n ; ++j) {
            for (int i = 1 ; i + (1 << j) - 1 <= n ; ++i) {
                T[i][j] = __gcd(T[i][j - 1], T[i + (1 << (j - 1))][j - 1]) ;
            }
        }
    }
    inline type query_max(int l, int r) {
        int len = logTable[r - l + 1] ;
        return max(T[l][len], T[r - (1 << len) + 1][len]) ;
    }
    inline type query_min(int l, int r) {
        int len = logTable[r - l + 1] ;
        return min(T[l][len], T[r - (1 << len) + 1][len]) ;
    }
    inline type query_gcd(int l, int r) {
        int len = logTable[r - l + 1] ;
        return __gcd(T[l][len], T[r - (1 << len) + 1][len]) ;
    }
} ;
