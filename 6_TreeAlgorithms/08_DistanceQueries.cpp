#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '  
#define _space_ <<' '<<
using namespace std;

int min_r(int a, int b, int n, int tree[]){
    a+=n; b+=n;
    int s=2e9;//around the maximum of an integer (greater than n is fine also for this problem)
    while (a<=b) {
        if (a%2==1) s=min(s,tree[a++]); 
        if (b%2==0) s=min(s,tree[b--]); 
        a/=2; b/=2;
    }
    return s;    
}

void upd_r(int k, int depth, int n, int tree[]){
    k += n;
    tree[k] = depth;
    for (k/=2; k>=1; k/=2) tree[k]=min(tree[2*k],tree[2*k+1]);
}



void DFS(int x, int x_prev, vector<int> Adj[], int d, int Tree[], int & idx, int Idx[], int n ){
    //no array of visited since we assume a graph that is tree. 
    //d is the depth, i is the iteration counter (when visiting and returning from nodes) of DFS 
    upd_r(idx, d, 2*n-1, Tree); 
    Idx[x] = idx ; 
    for(int const x_next:Adj[x]){
        if (x_next==x_prev) continue;
        idx ++;
        DFS(x_next, x, Adj, d+1, Tree, idx, Idx, n);  
        idx ++; 
        upd_r(idx, d, 2*n-1, Tree);    
    }
}

int main(){    
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    int n, q, a, b, Ia, Ib;
    cin >> n >> q;
    int Tree[2*(2*n-1)];//Distance from root while visiting the nodes using DFS. Using min-segment tree to store
    int idx=0, Idx[n];//Position of each node on the Tree. I.e. when DFS first found each node.
    vector <int> Adj[n];
    for (int i=0; i<n-1; i++){
        cin >> a >> b; a--; b--;
        Adj[a].push_back(b);
        Adj[b].push_back(a);
    }
    DFS(0, -1, Adj, 0, Tree, idx, Idx, n);
    for (int i=0; i<q; i++){
        cin >> a >> b; 
        Ia = Idx[a-1]; Ib = Idx[b-1];
        if (Ib<Ia) swap(Ia,Ib);
        cout << min_r(Ia, Ia, 2*n-1, Tree) + min_r(Ib, Ib, 2*n-1, Tree) -2* min_r(Ia, Ib, 2*n-1, Tree) _endl;
    }
}