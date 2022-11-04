#include <bits/stdc++.h>
#define int long long
#define ff first
#define ss second
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
using namespace std;

const long long inf = 1LL<<60; //1.5e18, max(long long)= 9e18 = 2^63
const int md = 1000000007;

pair<int,int> Fill_P(int P[][2], int adj[], bool Vis[], int node, int dist){
    //returns [ans, node_cycle] with ans being the answer for the node and node_cycle is the node 
    //with which this path entered the cycle. Returns [ans,-1] if there is no cycle in this path
    int node_cycle;
    if (!Vis[node]){
        Vis[node] = true;
        P[node][0] = dist;
        tie(P[node][1], node_cycle)= Fill_P(P, adj, Vis, adj[node], dist+1);
        if (node_cycle==-1 || node_cycle==node) return {P[node][1]+1,-1};
        else return {P[node][1],node_cycle};
    }
    else if (P[node][1]<0){
        //the node you visited is from this path (search of Fill_P)
        P[node][1] = dist-P[node][0];
        return {P[node][1], node};
    }
    else return {P[node][1]+1,-1};
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);    
    int n, b;
    cin >> n;
    int adj[n], P[n][2];//P[i] -> [dist_from_root_of_this_path, answer_for_node_i]
    bool Vis[n];
    for (int i=0; i<n; i++){
        cin >> b;
        adj[i] = b-1;
        P[i][1] = -1;
        Vis[i]=false;
    }
    for (int i=0; i<n; i++){
        if (Vis[i]) continue;
        Fill_P(P, adj, Vis, i, 0);
    }
    for (int i=0; i<n; i++) cout << P[i][1] _space;    
}