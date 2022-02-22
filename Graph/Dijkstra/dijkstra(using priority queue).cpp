vector < vector < pii > > g ;
int n, m ; 

void dijkstra(int s, vll& d, vi& p){
    d.assign(n + 1, Inf) ;
    p.assign(n + 1, -1) ;
    priority_queue < pair < ll, int >, vector < pair < ll, int > > , greater< pair < ll, int > > > pq ;
    d[s] = 0 ; 
    pq.push(make_pair(0, s)) ;
    while(!pq.empty()){
        int v = pq.top().second ;
        ll dv = pq.top().first ;
        pq.pop() ;
        if(dv != d[v])continue ;
        for(auto i : g[v]){
            if(d[v] + i.ss < d[i.ff]){
                d[i.ff] = d[v] + i.ss ;
                pq.push(make_pair(d[i.ff], i.ff)) ;
                p[i.ff] = v ;
            }
        }
    }
}
