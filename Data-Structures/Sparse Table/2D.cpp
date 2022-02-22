template <typename t> struct SparseTable2D {
    int n, m, logN, logM ;
    vector < vector < vector < vector < t > > > > table ;
    SparseTable2D(int _n = 0, int _m = 0) : n(_n), m(_m) {
        logN = 32 - __builtin_clz(n) ; // log2(n) + 1 ;
        logM = 32 - __builtin_clz(m) ;
        table.assign(n + 1, vector < vector < vector < t > > > (logN, vector < vector < t > > (m + 1, vector < t > (logM, 0)))) ;
    }

    inline void build_max_2D(vector < vector < t > > &a) {
        for (int i = 1 ; i <= n ; ++i) {
            for (int j = 1 ; j <= m ; ++j) {
                table[i][0][j][0] = a[i][j] ;
            }
            for (int j = 1 ; j < logM ; ++j) {
                for (int k = 1 ; k + (1 << j) - 1 <= m ; ++k)
                    table[i][0][k][j] = max(table[i][0][k][j - 1], table[i][0][k + (1 << (j - 1))][j - 1]) ;
            }
        }
        for (int j = 1 ; j < logN ; ++j) {
            for (int i = 1 ; i + (1 << j) - 1 <= n ; ++i) {
                for (int l = 0 ; l < logM ; ++l) {
                    for (int k = 1 ; k + (1 << l) - 1 <= m ; ++k) {
                        table[i][j][k][l] = max(table[i][j - 1][k][l], table[i + (1 << (j - 1))][j - 1][k][l]) ;
                    }
                }
            }
        }
    }
    inline t query_max_2D(int x1, int y1, int x2, int y2) {
        int logX = 31 - __builtin_clz(x2 - x1 + 1) ;
        int logY = 31 - __builtin_clz(y2 - y1 + 1) ;
        t max_R1 = max(table[x1][logX][y1][logY], table[x1][logX][y2 - (1 << logY) + 1][logY]) ;
        t max_R2 = max(table[x2 - (1 << logX) + 1][logX][y1][logY], table[x2 - (1 << logX) + 1][logX][y2 - (1 << logY) + 1][logY]) ;
        return max(max_R1, max_R2) ;
    }
} ;
