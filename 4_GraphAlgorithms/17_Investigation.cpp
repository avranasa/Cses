/* First Solution (Sol==1)
-Do Dijkstra  to find from 1 the minimum distance to all other nodes (except the
ones that need higher price to be reached than the minimum-price necessary to 
reach the final destination.) Alter the Dijkstra's algorith to  allow a node 
to be reached multiple times from different paths as long as all the paths reach
that node in the minimum-price. Keep all the edges with which this node is reached.
With the kept edges you have created a sub-graph that contains all possible minimum-price
paths from node 1 to node n and all paths from 1 to n are valid minimum-price paths
(in the second Solution (Sol==2) the sub-graph is represented by storing for each node 
all the other nodes pointing to that node). 
-DPF on the sub-graph to find for each node the tuple (X,Y,Z) where X is the number 
of (minimum-price) paths from k to node n, Y is the minimimum number of hops to reach 
from k to node n (in a minimum-price path) and Z the maximum number of hops.
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define INF 1e18
#define Mod 1000000007

void DFS_MinPriceRoutes_SubGraph(vector<int> adj[], int node, vector <tuple<int,int,int>> & Ans ){
    //finds the number of paths from "node" to final, the minimum & maximum number 
    //of edges such a path can have
    int Paths=0, Min_Flights=1e9, Max_Flights=0, p, m, M;
    for(int next_node:adj[node]){
        tie(p,m,M) = Ans[next_node];
        if (p == -1) {
            //not yet Visited the next_node
            DFS_MinPriceRoutes_SubGraph(adj, next_node, Ans);
            tie(p,m,M) = Ans[next_node];
        }        
        if (p == 0) continue; //Last city can not be reached from that node
        Paths = (Paths+p)%Mod;     
        Min_Flights = min(Min_Flights, m+1);
        Max_Flights = max(Max_Flights, M+1);   
    }
    Ans[node] = {Paths, Min_Flights, Max_Flights};
}

void DFS_MinPriceRoutes_MinDist(vector<pair<int,int>> adj[], int node, vector <tuple<int,int,int>> & Ans, vector <ll> & MinDist, ll path_dist){
    //finds the number of paths from "node" to final, the minimum & maximum number 
    //of edges such a path can have
    //if MinDist is provided then each step of is taken only if the node is reached in a minimum distance
    //path (according to MinDist)
    int Paths=0, Min_Flights=1e9, Max_Flights=0, p, m, M;
    for(auto next_node:adj[node]){
        if (path_dist+next_node.second > MinDist[next_node.first]) continue;
        tie(p,m,M) = Ans[next_node.first];
        if (p == -1) {
            //not yet Visited the next_node
            DFS_MinPriceRoutes_MinDist(adj, next_node.first, Ans, MinDist, path_dist+next_node.second);
            tie(p,m,M) = Ans[next_node.first];
        }        
        if (p == 0) continue; //Last city can not be reached from that node
        Paths = (Paths+p)%Mod;     
        Min_Flights = min(Min_Flights, m+1);
        Max_Flights = max(Max_Flights, M+1);   
    }
    Ans[node] = {Paths, Min_Flights, Max_Flights};
}

int main(){
    int SOL = 3;
    int n, m, a, b, c;
    cin >> n >> m;
    vector <pair<int,int>> adj[n];
    for(int i=0; i<m; i++){
        cin >> a >> b >> c;
        adj[a-1].push_back({b-1,c});
    }

    vector <ll> MinPrices(n,INF);
    vector <bool>processed(n,false);
    vector <tuple<int,int,int>> Ans(n, {-1,0,0}); //#paths=-1 means it is not yet visited
    ll total_price;    
    MinPrices[0] = 0;
    if (SOL==1){
        //1st version
        //Computes sub_adj[i] as the set of nodes can be reached FROM i
        priority_queue <tuple<ll,int,int>> Q;
        Q.push({-INF,0,0});
        vector <int> sub_adj[n];//the sub-graph of mimimum prices paths
        while (!Q.empty()){
            tie(total_price, b, a) = Q.top(); //current node "b" coming from "a"
            Q.pop();
            if (MinPrices[b]==-total_price) sub_adj[a].push_back(b);  
            if (MinPrices[n-1]< -total_price) break; //Not gaining much
            if (processed[b]) continue; 
            processed[b] = true;
            for(auto d: adj[b]){
                total_price = MinPrices[b] + d.second;
                if (total_price < MinPrices[d.first]){
                    Q.push({-total_price, d.first, b});
                    MinPrices[d.first] = total_price;// Here you find the minimum price
                }
                else if (total_price == MinPrices[d.first]){
                    if (processed[d.first]) sub_adj[b].push_back(d.first); 
                    else  Q.push({-total_price, d.first, b});//VERY SLOW... It sometimes increases a lot the Queue
                }
            }        
        }    
        Ans[n-1] = {1,0,0};//Trivial initialization for the last node. (i.e. only one path exists from the last to the last node with 0 flights...)
        DFS_MinPriceRoutes_SubGraph(sub_adj, 0, Ans);
        tie(a,b,c) = Ans[0];
        cout << MinPrices[n-1] << " " << a << " " << b << " " << c;
    }
    else if (SOL==2){
        //2 version. 
        //Computes sub_adj[i] as the set of nodes that can reach TO i
        priority_queue <tuple<ll,int>> Q;
        Q.push({-INF,0});
        vector <int> sub_adj[n];//the sub-graph of mimimum prices paths
        while (!Q.empty()){
            tie(total_price, b) = Q.top(); 
            Q.pop();
            if (MinPrices[n-1]< -total_price) break; //Not gaining much
            if (processed[b]) continue; 
            processed[b] = true;
            for(auto d: adj[b]){
                total_price = MinPrices[b] + d.second;
                if (total_price < MinPrices[d.first]){
                    Q.push({-total_price, d.first});
                    MinPrices[d.first] = total_price;
                    sub_adj[d.first].clear();
                    sub_adj[d.first].push_back(b); //if this and previous line are omitted it runs fast enough (but wrong)
                }
                else if (total_price == MinPrices[d.first])  sub_adj[d.first].push_back(b); // if this line is omitted it runs
                                                                                            //fast enough but wrong
            }        
        }
        Ans[0] = {1,0,0};//Trivial initialization for the first node since we inverted everything 
        DFS_MinPriceRoutes_SubGraph(sub_adj, n-1, Ans);
        tie(a,b,c) = Ans[n-1];
        cout << MinPrices[n-1] << " " << a << " " << b << " " << c;
    }
    else if (SOL==3){
        //3 version. Maybe slightly faster.
        //There is no sub_adj[i]. In the DFS after Dijkstra you also pass the minimum distances/prices 
        //per node and the DFS only consider paths with minimum prices.
        priority_queue <tuple<ll,int>> Q;
        Q.push({-INF,0});
        while (!Q.empty()){
            tie(total_price, b) = Q.top(); Q.pop();
            if (processed[b]) continue; 
            processed[b] = true;
            for(auto d: adj[b]){
                total_price = MinPrices[b] + d.second;
                if (total_price < MinPrices[d.first]){
                    Q.push({-total_price, d.first});
                    MinPrices[d.first] = total_price;
                }
            }        
        }    
        Ans[n-1] = {1,0,0};//Trivial initialization for the last node. (i.e. only one path exists from the last to the last node with 0 flights...)
        DFS_MinPriceRoutes_MinDist(adj, 0, Ans, MinPrices, 0);       
        tie(a,b,c) = Ans[0];
        cout << MinPrices[n-1] << " " << a << " " << b << " " << c;
    }
}