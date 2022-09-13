#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main(){
    int n, m, a, b, node;
    cin >> n >>m;
    vector <int> Adj[n], Cities2connect;
    for(int e=0; e<m; e++){
        cin >> a >> b;
        Adj[a-1].push_back(b-1);
        Adj[b-1].push_back(a-1);
    }
    bool Visited[n]={};
    for (int i=0;i<n;i++){
        if (Visited[i]) continue;
        Visited[i] = true;
        Cities2connect.push_back(i);
        queue <int> Q;
        Q.push(i);
        while (!Q.empty()){
            node = Q.front(); Q.pop();
            for (int next_node:Adj[node]){
                if (Visited[next_node]) continue;
                Q.push(next_node);
                Visited[next_node] = true;
            }
        }
    }
    cout <<Cities2connect.size()-1 << endl;
    for(int i=1; i<Cities2connect.size();i++) cout << Cities2connect[i-1]+1<<" "<< Cities2connect[i]+1 << endl;
    
}