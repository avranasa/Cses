//This is the greedy way and it works. But I have not proved mathematically that is 
//always correct. A dynamic programming approach should also work and it is for sure
//correct (...for each child you solve the problem by counting the number of matching 
//and if this child (and root of the subtree) is included in a matching and then you 
//solve the problem for the parent...)

#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
using namespace std;
const long long inf = 1LL<<60; //1.5e18, max(long long)= 9e18 = 2^63
const int md = 1000000007;


void NumMatchings_dfs(vector <int> adj[], int node, int prev_node, vector<bool> & Included){
    for (int child_node: adj[node]){
        if (child_node == prev_node) continue;
        NumMatchings_dfs(adj, child_node, node, Included);
        if (!Included[node] && !Included[child_node]){
            Included[node] = true;
            Included[child_node] = true;
        }
    }
    if ( !Included[node] && !Included[prev_node] && node!=prev_node){
        Included[node] = true;
        Included[prev_node] = true;
    }        
}

int main (){
    int n, a, b, ans=0;
    cin >> n;
    vector <int> adj[n];//the input is for sure a tree
    for (int i=0; i<n-1; i++){
        cin >> a >> b;
        adj[a-1].push_back(b-1);
        adj[b-1].push_back(a-1);
    }
    vector <bool> Included(n,false);//Contains all the nodes that are include in a matching
    NumMatchings_dfs(adj, 0, 0, Included);//each edge is bidirectional so you start wherever you want.
    for (int i=0; i<n; i++) { 
        ans += Included[i]; 
        //cout << Included[i] << " "; 
    }
    cout << ans/2;
}
