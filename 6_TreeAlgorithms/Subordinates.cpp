#include <bits/stdc++.h>
using namespace std;

void dfs_count_children(int node, vector<int> adj[], vector<int> & num_children){
    int s = 0;
    for(int next_node: adj[node]){
        dfs_count_children(next_node, adj, num_children);
        s += num_children[next_node] + 1;
    }
    num_children[node] = s;
}

int main(){
    //each employee has only ONE direct boss
    int n, b;
    cin >> n;
    vector <int> adj[n], num_children(n);
    for (int i=1; i<n; i++){
        cin >> b;
        adj[b-1].push_back(i);//directed graph (from boss to subordinate)
    }
    dfs_count_children(0, adj, num_children);
    for(int sub : num_children) cout<< sub << " ";
}
