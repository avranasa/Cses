
#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
using namespace std;
const long long inf = 1LL<<60; //1.5e18, max(long long)= 9e18 = 2^63
const int md = 1000000007;

pair<int,int> find_sol(vector<int> adj[], int node, int prev_node){
    int candidate_diam=1, max_node2leaf=0, second_max_node2leaf=-1000000, a, b;
    for (int next_node:adj[node]){
        if (next_node == prev_node) continue;
        tie(a,b) = find_sol(adj, next_node, node);
        if (max_node2leaf>0){
            if (b<=max_node2leaf) second_max_node2leaf = max(second_max_node2leaf,b);
            else second_max_node2leaf = max_node2leaf;}
        if (b>max_node2leaf) max_node2leaf = b;            
        candidate_diam = max(candidate_diam,a);
    }  
    if (candidate_diam < max_node2leaf+1+second_max_node2leaf)
        candidate_diam = max_node2leaf+1+second_max_node2leaf;
    return {candidate_diam, max_node2leaf+1};
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);    
    int n,a,b;
    cin >> n;
    vector <int> adj[n];
    for (int i=0; i<n-1; i++){
        //you know that you have a tree so a connected graph
        cin >> a >> b;
        adj[a-1].push_back(b-1);
        adj[b-1].push_back(a-1);
    }
    tie(a,b) = find_sol(adj, 0, -1);
    cout << max(a,b)-1;  
}