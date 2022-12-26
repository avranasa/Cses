#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '  
#define int long long
#define _space_ <<' '<<
using namespace std;
const long long inf = 1LL<<60; //1.5e18, max(long long)= 9e18 = 2^63
const int md = 1000000007;

void dfs_1(vector <int> Adj[], vector <int> & Num_nodes, vector <int> & Dist_ch, int node, int prev_node){
    int n_nodes = 1, dist = 0;
    for (int next_node: Adj[node]){
        if (next_node==prev_node) continue;
        dfs_1(Adj, Num_nodes, Dist_ch, next_node, node);
        n_nodes += Num_nodes[next_node];
        dist += Dist_ch[next_node];
    }
    Num_nodes [node] = n_nodes;
    Dist_ch[node] = dist + n_nodes - 1;
}

void dfs_2(vector <int> Adj[], vector <int> & Num_nodes, vector <int> & Dist_ch, vector <int> & Dist, int node, int prev_node, int n_nodes_tot){
    int dist_without_ch;//distance substracting the subtree of the child
    for (int next_node: Adj[node]){
        if (next_node==prev_node) continue;
        dist_without_ch = Dist[node] - Dist_ch[next_node] - Num_nodes[next_node];
        //Update number of nodes from subtree to total
        Dist[next_node] = dist_without_ch + n_nodes_tot - Num_nodes[next_node] + Dist_ch[next_node];
        dfs_2(Adj, Num_nodes, Dist_ch, Dist, next_node, node, n_nodes_tot);
    }
}

signed main(){
    int a, b, n;
    cin >> n;
    vector <int> adj[n];
    for (int i=0; i<n-1; i++){
        cin >> a >> b;
        adj[a-1].push_back(b-1);
        adj[b-1].push_back(a-1);
    }
    vector <int> Num_nodes(n,0), Dist_ch(n,0);//for each node i we save: 1) the number of nodes the subtree 
            //with root the node i has and 2) the distance of the subtree (if only the subtree is considered)
    dfs_1(adj, Num_nodes, Dist_ch, 0, 0);  

    vector <int> Dist(n,0);
    Dist[0] = Dist_ch[0];
    dfs_2(adj, Num_nodes, Dist_ch, Dist, 0, 0, n);
    for (int d: Dist) cout << d _space ;
}