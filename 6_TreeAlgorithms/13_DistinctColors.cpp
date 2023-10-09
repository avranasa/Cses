#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '  
#define _space_ <<' '<<
using namespace std;

void DFS(int x, int x_prev, vector <int> Adj[], set <int> C[], int Ans[]){
    for (int x_new : Adj[x]){
        if (x_new == x_prev) continue;
        DFS(x_new, x, Adj, C, Ans);
        if (C[x].size() > C[x_new].size()) C[x].insert(C[x_new].begin(), C[x_new].end());
        else{
            C[x_new].insert(C[x].begin(), C[x].end());
            swap(C[x], C[x_new]);
        }
    }
    Ans[x] = C[x].size();
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    int n, a, b, c;
    cin >> n;
    // note that if I declare the Ans[], C[], Adj[] outside the main before
    // DFS it gets slightly slower!
    int Ans[n]; 
    set <int> C[n];//C[x] temporarily computes the number of distinct colors
                  //of node x and the correct answer is stored in Ans[x]
                  //Btw, here unordered_set is 20% slower than just set!
    vector <int> Adj[n];
    for (int i=0; i<n; i++) {
        cin >> c;
        C[i].insert(c);
    }
    for (int i=0; i<n-1; i++) {
        cin >> a >> b; a--; b--;
        Adj[a].push_back(b);
        Adj[b].push_back(a);
    }
    
    DFS(0, -1, Adj, C, Ans);

    for(int i=0; i<n; i++) cout << Ans[i] _space ;
}