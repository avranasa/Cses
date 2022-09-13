#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <unordered_set>
#include <algorithm>

using namespace std;

int main(){
    int n , m, N_nodes=0;
    cin >> n >> m;
    char c;
    bool M[n+2][m+2]={};
    unordered_set <int> AllNodes;
    int Id[n+2][m+2];//each floor is given a number from 0 to NumberOfSquares-1
    for (int i=1; i<=n; i++){
        for (int j=1;j<=m;j++){
            cin >> c;
            if (c=='.') {
                M[i][j]=true;
                Id[i][j]=N_nodes;
                AllNodes.insert(N_nodes);
                N_nodes++;  
            }
        }            
    }

    vector <vector <int>> Net;
    for (int i=1; i<=n; i++){
        for (int j=1;j<=m;j++){
            if (M[i][j]){                
                vector <int> Node_adj; 
                if (M[i-1][j]) Node_adj.push_back(Id[i-1][j]);        
                if (M[i+1][j]) Node_adj.push_back(Id[i+1][j]);        
                if (M[i][j-1]) Node_adj.push_back(Id[i][j-1]);        
                if (M[i][j+1]) Node_adj.push_back(Id[i][j+1]);  
                Net.push_back(Node_adj); // because I see the nodes in the same way as when I read them I know that 
                                         // I check the nodes in an "increased" Id way... so no need to do Net[Id[i][j]].push_back(Node_adj)
            }
        }            
    }    

    
    int N_components = 0, nod;
    bool Visited[N_nodes]={};
    queue <int> Q;
    /* Slightly faster the implementation below
    for(int visit=0; visit<N_nodes; visit++){ 
        if (Visited[visit]) continue;
        Q.push(visit);
        Visited[visit]=true;
        N_components++;
        while (!Q.empty()){
            nod = Q.front(); Q.pop();
            for(int next_nod: Net[nod]){
                if (!Visited[next_nod]) {
                    Q.push(next_nod);           
                    Visited[next_nod] = true;   
                }
            }                   
        }  
    } */
    
    while(!AllNodes.empty()){ 
        nod = *AllNodes.begin(); 
        AllNodes.erase(nod);
        Q.push(nod);
        Visited[true];
        N_components++;
        while (!Q.empty()){
            nod = Q.front(); Q.pop();
            for(int next_nod: Net[nod]){
                if (!Visited[next_nod]) {
                    Q.push(next_nod);                                         
                    AllNodes.erase(next_nod); 
                    Visited[next_nod] = true;   
                }
            }                   
        }  
    }
   

    cout << N_components;
}