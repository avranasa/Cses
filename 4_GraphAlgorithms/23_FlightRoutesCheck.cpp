#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
using namespace std;



int FindUnreachableNode(int root, vector<int> A[], int n){
    //Given a graph A and starting node root it returns some node 
    //that cannot be reached from root. If all nodes can be reached from root
    //root it returns -1.
    queue<int> q;
    bool visited[n] = {false};
    q.push(root);
    while (!q.empty()){
        int x = q.front(); q.pop();
        if (visited[x]) continue;
        visited[x] = true;
        for(int x_new:A[x])
            if (!visited[x_new]) q.push(x_new);
    }
    for(int x=0; x<n; x++)
        if (!visited[x]) return x;
    return -1;
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);  cout.tie(0);
    int n, m, a, b, WAY = 1;
    cin >> n >> m;
    if (WAY==1){
        // In order to be able to go from anywhere to everywhere then given any city,
        // this city should connect to all other cities and all other cities also 
        // have a path back to this city.... Exists a cycle connecting all cities.
        vector <int> A[n], A_inv[n];
        for(int i=0; i<m; i++){
            cin >> a >> b;
            A[a-1].push_back(b-1);
            A_inv[b-1].push_back(a-1);
        }
        //From city 0 to the rest
        b = FindUnreachableNode(0, A, n);
        if (b>=0){
            cout << "NO\n1 "<<b+1;
            return 0;
        }        
        //From the rest of the cities to 0
        b = FindUnreachableNode(0, A_inv, n);
        if (b>=0){
            cout << "NO\n"<<b+1<<" 1";
            return 0;
        }
        cout << "YES";
    }
    else if (WAY==2){
        // Not implemented because it is similar to 24_PlanetsAndKingdom.cpp. You do one DFS 
        // and if any node B is unvisited when starting from node A or you find that 
        // FindCapital(ToCapital[],A) != FindCapital(ToCapital[],B) you output "NO\n A B"...

    }
}
