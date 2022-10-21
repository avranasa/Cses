#include <bits/stdc++.h>
using namespace std;
#define Mod 1000000007
#define ll long long

void topological_sort(vector<int> adj[], vector<int> & sorted_nodes, vector<bool> & sorted, int node){
    for (int next_node:adj[node])
        if (! sorted[next_node])  topological_sort(adj, sorted_nodes, sorted, next_node);
    sorted[node] = true;
    sorted_nodes.push_back(node);
}

int main(){
    int n,m,a,b;
    cin >> n >> m;
    vector<int> adj[n], sorted_nodes;
    for (int i=0; i<m; i++){
        cin >>a >> b;
        adj[a-1].push_back(b-1);
    }

    //topological sort
    vector<bool> sorted(n,false);//we know that there is no directed cycle so we only
                                //have to check per node if it is sorted
    topological_sort(adj, sorted_nodes, sorted, 0);//we only care about nodes reachable from node 0 (i.e. not sorting the rest)
    
    //Number of paths
    map <int, int> Node2Idx;
    for(int i = 0; i<sorted_nodes.size(); i++) Node2Idx[sorted_nodes[i]]=i;
    if (Node2Idx.find(n-1) == Node2Idx.end()) cout << 0 ;
    else{
        vector <ll> Paths(sorted_nodes.size(),0);
        Paths.back() = 1; //the last element of Paths correspond to the level 1 (or node 0 of the graph)
        for (int i=sorted_nodes.size()-1; i>=0; i--)
            for (auto x: adj[sorted_nodes[i]]) Paths[Node2Idx[x]] = (Paths[Node2Idx[x]] + Paths[i]) % Mod;  

        cout << Paths[Node2Idx[n-1]];    
    }
}