#include <vector>
#include <iostream>
using namespace std;

void DFS(vector <int> * Adj, bool * Visited, int node, int prev_node, vector<int> & Sol){
    if (!Visited[node]){
        Visited[node] = true;
        for(int next_node: Adj[node]){
            if (prev_node == next_node) continue;//not using the same edge twice
            DFS(Adj,Visited,next_node, node, Sol);
            if (Sol.size() == 1) Sol.push_back(node+1);
            else if ((Sol.size()>1)  && (Sol.back()!=Sol[0])) Sol.push_back(node+1);
            if (!Sol.empty()) return;
        }
    }
    else if (Sol.empty()) Sol.push_back(node+1);
}

int main(){
    int n , m, a, b, root;
    cin >> n >> m;
    vector <int> Adj[n];
    bool Visited[n]={};
    for ( int i=0; i<m; i++){
        cin >> a >> b;
        Adj[a-1].push_back(b-1);
        Adj[b-1].push_back(a-1);
    }
    bool Visited_all_nodes = false;
    while (!Visited_all_nodes){
        Visited_all_nodes = true;
        for(int i;i<n;i++){
            if (!Visited[i]){
                root = i;
                Visited_all_nodes = false;
                break;
            }
        }
        vector <int> Sol;
        DFS(Adj, Visited, root, -1, Sol);
        if (Sol.size()>=2) {
            cout << Sol.size() <<endl;
            for(int node : Sol) cout<< node << " "; 
            break;
        }
    }
    if (Visited_all_nodes) cout<< "IMPOSSIBLE";
    
}
