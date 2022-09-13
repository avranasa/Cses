#include <bits/stdc++.h>
using namespace std;
#define INF 8e18//for long long 9e18 is the maximum... I put a bit less so as to be able to add a number (less than 1e18...) without going to the minus


int main(){
    int n,m,a,b;
    cin >> n >> m;
    long long Dist[n], c, dist;
    for(int i=1;i<n;i++) Dist[i] = INF;
    bool Visited[n] = {0};
    vector < pair<long long,int> > Adj[n];
    for (int i=0; i<m; i++){
        cin >> a >> b >> c;
        Adj[a-1].push_back({c, b-1});
    }
    priority_queue< pair<long long, int>> Q;
    Q.push({0,0});
    Dist[0] = 0;
    
    while (!Q.empty()){
        a = Q.top().second;
        Q.pop();
        if (Visited[a]) continue;
        Visited[a] = true;
        for(auto p: Adj[a]){
            b = p.second;
            if (Visited[b]) continue;
            dist = p.first + Dist[a]; 
            if (dist<Dist[b]){
                Dist[b] = dist;
                Q.push({-dist,b});//the minus because we push the - distances in the queue which is a max-heap
            }
        }            
    }
    /*
    //Bellman-Ford is slow
    vector<tuple <int, int, long long>> Edges;
    for (int i=0;i<m;i++){
        cin>>a>>b>>c;
        Edges.push_back({a-1,b-1,c});        
    }
    Visited[0]=true;
    for (int i =0;i<n-1;i++){
        for(auto edge: Edges){
            tie(a,b,c) = edge;
            if (!Visited[a]) continue;
            if (!Visited[b]){
                Visited[b]=true;
                Dist[b] = Dist[a]+c;
            }
            Dist[b] = min(Dist[b], Dist[a]+c);
        }
    }
    */
    for(auto d:Dist) cout<<d<<" ";
}