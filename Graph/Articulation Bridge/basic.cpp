int backEdges[N], level[N] ;
vector < vector < int > > g ;
vector < pii > bridges ;

void dfs(int s, int p = 0) {
    level[s] = 1 + level[p] ;
    for (int i : g[s]) {
        if (!level[i]) {
            dfs(i, s) ;
            backEdges[s] += backEdges[i] ;
        }
        else {
            if (i == p)continue ;
            if (level[i] > level[s])--backEdges[s] ;
            else if (level[i] < level[s])++backEdges[s] ;
        }
    }
    if (backEdges[s] == 0 and s != p and p > 0)bridges.push_back(make_pair(p, s)) ;
}
