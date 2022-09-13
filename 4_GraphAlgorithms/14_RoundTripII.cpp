#include <bits/stdc++.h>
#define ll long long

using namespace std;

void dfs(vector <int> Adj[], int node, bool Visited[], bool OnPath[], vector <int> &Cycle){
    if (Visited[node]) return;
    Visited[node] = true;
    for (auto next_node: Adj[node]){
        if (OnPath[next_node]){
            Cycle.push_back(next_node);
            Cycle.push_back(node);
            return;
        }
        OnPath[next_node] = true;
        dfs(Adj, next_node, Visited, OnPath, Cycle);
        if (!Cycle.empty()) {
            if (Cycle.front() == Cycle.back()) return;
            Cycle.push_back(node);
            return;
        }
        OnPath[next_node] = false;
    }
}

int main(){
    int n, m, a, b;
    cin >> n >> m;
    vector <int> Adj[n], Cycle;
    for (int i=0; i<m; i++){
        cin >> a >> b; 
        Adj[a-1].push_back(b-1);
    }

    bool Visited[n]={}, OnPath[n]={};
    for(int root=0; root<n; root++){
        if (Visited[root]) continue;
        OnPath[root] = true;
        dfs(Adj, root, Visited, OnPath, Cycle);
        OnPath[root] = false;
        if (!Cycle.empty()) break;
    }
    
    
    if (Cycle.empty()) cout <<"IMPOSSIBLE";
    else{
        cout << Cycle.size() << endl;
        for (auto it=Cycle.rbegin();it!=Cycle.rend(); it++) cout<<*it+1<<" ";
    }


}