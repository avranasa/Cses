//Create the graph with component and represent each component as one node with number of coins 
//equal to the sum of coins of all nodes belonging to that component.
#include <bits/stdc++.h>
#define int long long
#define ff first
#define ss second
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
using namespace std;

void DFS_create_stack(int x, bool visited[], vector<int> Adj[], stack<int> & S){
    visited[x] = true;
    for(int x_new: Adj[x]){
        if (visited[x_new]) continue;
        DFS_create_stack(x_new, visited, Adj, S);
    }
    S.push(x);
}

void DFS_find_comp(int x, bool visited[], vector<int> Adj_inv[], int Comp[], int c){
    visited[x] = true;
    Comp[x] = c;
    for(int x_new: Adj_inv[x]){
        if (visited[x_new]) continue;
        DFS_find_comp(x_new, visited, Adj_inv, Comp, c);
    }
}

void DFS_max_K(int c, set<int> Adj[], int K_max[], int K_comp []){   
    //assuming no cycles on component graph
    int k_max_child = 0;
    for(int c_new: Adj[c]){
        if (K_max[c_new]==0) DFS_max_K(c_new, Adj, K_max, K_comp);
        k_max_child = max<int>(K_max[c_new], k_max_child );
    }
    K_max[c] = K_comp[c] + k_max_child;
}
 
signed main(){
    ios::sync_with_stdio(0); cin.tie(0);  cout.tie(0);
    int n, m, a, b, x;
    cin >> n >> m;
    vector <int> Adj[n], Adj_inv[n];
    int K[n];
    for (int i=0; i<n; i++) cin >> K[i];
    for(int i=0; i<m; i++){
        cin >> a >> b;
        Adj[a-1].push_back(b-1);
        Adj_inv[b-1].push_back(a-1);
    }

    //Creating the component graph
    bool visited[n]={false};
    stack<int> S;
    for(int x=0; x<n; x++){
        if (visited[x]) continue;
        DFS_create_stack(x, visited, Adj, S);
    }
    int Comp[n]={}, N_comp=0;
    for(int x=0; x<n; x++) visited[x] = false;
    while(!S.empty()){
        x = S.top();
        if (visited[x]){ S.pop(); continue;}
        N_comp ++;
        DFS_find_comp(x, visited, Adj_inv, Comp, N_comp-1);        
    } 
    set<int> Adj_comp[N_comp];
    int K_comp[N_comp] = {0};//the sum of coins per component
    for(int x=0; x<n; x++){
        K_comp[Comp[x]] += K[x];
        for(int x_to:Adj[x]) if (Comp[x]!=Comp[x_to]) Adj_comp[Comp[x]].insert(Comp[x_to]);
    }
    //for(int c=0; c<N_comp; c++) cout << K_comp[c] << " ";

    //Computing for each component the max of coins can be colected if starting 
    //from any node of that component
    int K_max[N_comp] = {0}, k_max = 0;
    for(int c=0; c<N_comp; c++){
        if (K_max[c]>0) continue;//K_max also play the role of the "visited" array
        DFS_max_K(c, Adj_comp, K_max, K_comp);
    }
    for(int c=0; c<N_comp; c++) k_max = max(k_max, K_max[c]);
    cout << k_max;
}