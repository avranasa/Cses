#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <utility>
using namespace std;

int main(){
    int n, m;
    char c;
    cin >>n >> m;
    int Id_nodes[n+2][m+2], start_node, end_node, id_node=0;
    bool M[n+2][m+2]={};
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            cin >> c;
            if (c=='#') continue;
            M[i][j]=true;
            Id_nodes[i][j]=id_node;
            if (c=='A') start_node = id_node;
            if (c=='B') end_node = id_node;
            id_node ++;
        }
    }
    
    int N_nodes = id_node;
    vector<pair <char,int>> Net[N_nodes];//the char is FROM node (i,j)
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            if (!M[i][j]) continue;            
            vector<pair <char,int>> Next_nodes;
            if (M[i-1][j]) Next_nodes.push_back({'U', Id_nodes[i-1][j]});
            if (M[i+1][j]) Next_nodes.push_back({'D',Id_nodes[i+1][j]});
            if (M[i][j-1]) Next_nodes.push_back({'L',Id_nodes[i][j-1]});
            if (M[i][j+1]) Next_nodes.push_back({'R',Id_nodes[i][j+1]});
            Net[Id_nodes[i][j]] = Next_nodes;
        }
    }
    
    bool visited[N_nodes]={};
    pair <char,int> LastMove[N_nodes];
    int nod;
    queue <int> Q;
    Q.push(start_node);
    visited[start_node]=true;
    while (!Q.empty()){
        nod = Q.front(); Q.pop();
        for(auto next_nod: Net[nod]){
            if (visited[next_nod.second]) continue;
            visited[next_nod.second] = true;
            Q.push(next_nod.second);
            LastMove[next_nod.second]={next_nod.first,nod};
        }                
    }
    if (!visited[end_node]){
        cout << "NO";
        return 0;
    }
    cout << "YES";    
    stack <char> seq;
    nod=end_node;
    while(nod != start_node){    
        seq.push(LastMove[nod].first);
        nod = LastMove[nod].second;
    }
    cout << endl << seq.size()<< endl;
    while(!seq.empty()){
        cout << seq.top();
        seq.pop();
    }
}