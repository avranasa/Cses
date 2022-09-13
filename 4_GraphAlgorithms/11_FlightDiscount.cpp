#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define INF 2e18

/*
think of the following graph:
5 5
1 4 50
1 2 12
2 3 12
3 4 12
4 5 1000
... When you reach the node 4 the best path is 1->4 but in order to go optimally to 5 a completely different path leads to 4,
which is 1->2->3->4. The first path is the best to reach to 4 if you have already used the discount but the second is the best
if you want to use it latter... So if using a single Dijkstra's priority queue do you order by the nodes by the "total cost" with
or without the discount?

Two Dijkstra. First one where you use the discount only in the last edge. Second one where in the priority queue you order the 
nodes by the "total cost" when already the discount was used. Whenever you check a new node you compare if either you arrive to 
that node with using the discount not in the last edge or with using it in the last edge and take into account the previous 
Dijkstra. I want that whenever you state a node as visited it means that in that point there is no way you could reach some other
unvisited city (using the discount) with "total cost" less than what spent to reach that city.

https://usaco.guide/problems/cses-1195-flight-discount/solution <-- check here for another 2 solutions... (the second one is similar to mine)
*/


int main(){
    int n, m, a, b;
    cin >> n >> m;
    ll d, Dist[n], Dist_NoDiscount[n], c;
    for(int i=0;i<n;i++) {Dist[i]=INF, Dist_NoDiscount[i]=INF;}
    bool Visited [n]={false}, InQueue[n]={false};
    vector<pair<int,ll>> Adj[n];
    for (int i=0; i<m; i++){
        cin >> a >> b >> c;
        Adj[a-1].push_back({b-1,c});
    }
    priority_queue<pair<ll, int>> Q;

    //1st Dijkstra where discount only in the last edge
    Dist_NoDiscount[0]=0;
    Q.push({0,0});
    while (!Q.empty()){
        a = Q.top().second; Q.pop();
        if (Visited[a]) continue;
        Visited[a] = true;
        for(auto p : Adj[a]){
            tie(b,c) = p;
            if (Visited[b]) continue;
            d = Dist_NoDiscount[a] + c;
            if (Dist_NoDiscount[b]> d){
                Dist_NoDiscount[b] = d;
                Dist[b] = min(Dist[b],Dist_NoDiscount[a] + c/2);
                Q.push({-d,b});
            }
        }
    }
    
    //2nd Dijkstra where discount can be used whenever the passenger desires
    for (int i=0; i<n; i++) Visited[i]=false;
    Dist[0]=0;
    Q.push({0,0});
    InQueue[0] = true;
    while (!Q.empty()){
        a = Q.top().second; Q.pop();
        InQueue[a] = false;
        if (Visited[a]) continue;
        Visited[a] = true;
        for(auto p : Adj[a]){
            tie(b,c) = p;
            if (Visited[b]) continue;
            d = Dist[a] + c;
            if ((Dist[b] < d) && (InQueue[b])) continue;// A node b can have (Dist[b] < d) just 
                    //because from the previous Dijkstra we found a good path to it with the last
                    //edge being discounted. This node even if stated as not visited and has a
                    //good Dist[b], it can be that it was not yet considered by this Dijkstra loop,
                    //so we have to push it in the queue
            Dist[b] = min(d,Dist[b]);
            Q.push({-Dist[b],b});
        }
    }    
    
    cout << Dist[n-1];
}

