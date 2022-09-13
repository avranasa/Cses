#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

int main(){
    int n, m, a, b;
    cin >> n >> m;
    vector <int> Adj[n];
    for (int i=0; i<m; i++){
        cin >> a >> b;
        Adj[a-1].push_back(b-1);
        Adj[b-1].push_back(a-1);
    }


    queue <int> Nodes;
    bool Visited[n]={};
    int PrevNode[n], nod;
    Nodes.push(0);
    Visited[0]=true;
    while(!Nodes.empty()){
        nod = Nodes.front();
        Nodes.pop();      
        for(int next_nod:Adj[nod]){
            if (Visited[next_nod]) continue;
            PrevNode[next_nod]=nod;
            Visited[next_nod]=true;
            Nodes.push(next_nod);
        }
    }

    if (!Visited[n-1]) {
        cout << "IMPOSSIBLE";
        return 0;
    }
    stack <int> route;
    route.push(n-1);
    while(route.top()!=0){
        route.push(PrevNode[route.top()]);
    }
    cout << route.size()<< endl;
    while(!route.empty()){
        cout<<route.top()+1<< " ";
        route.pop();
    }
}