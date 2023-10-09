/*
For each node x you keep a variable v_x initialized to 0. For a path between 
node a and b, do v_a++ and v_b++ and if c is their lowest common ancestor then 
do v_c--. Also do to the parent d of c v_d--.
Start a DFS from root (root is set arbitrarily from the very beginning).
To compute the number of paths of node x do a DFS that takes action only
when returning to a node x that has some children y1, y2,y3,... Then do
v_x = v_x + v_y1 + v_y2 + v_y3 +... After the DFS the v_x of each node is
the answer.
*/

#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '  
#define _space_ <<' '<<
using namespace std;

int min_r(int a, int b, int n, int tree[][2]){
    //returns node with minimum depth in the given range
    a+=n; b+=n;
    int node_min, d_min = 2e9;//around the maximum of an integer (greater than n is fine also for this problem)
    while (a<=b) {
        if (a%2==1) {
            if (d_min > tree[a][1]){
                d_min = tree[a][1];
                node_min = tree[a][0];
            }
            a++;
        }
        if (b%2==0) {
            if (d_min > tree[b][1]){
                d_min = tree[b][1];
                node_min = tree[b][0];
            }
            b--;
        } 
        a/=2; b/=2;
    }
    return node_min;    
}

void upd_r(int k, int depth, int node, int n, int tree[][2]){
    int k_min;
    k += n;
    tree[k][0] = node;
    tree[k][1] = depth;
    for (k/=2; k>=1; k/=2) {
        k_min = (tree[2*k][1]<tree[2*k+1][1]) ? 2*k : 2*k+1;
        tree[k][0]=tree[k_min][0];
        tree[k][1]=tree[k_min][1];        
    }
}

void DFS(int x, int Par[], vector<int> Adj[], int tree[][2], int & idx, int Idx[], int depth, int n ){
    upd_r(idx, depth, x, 2*n-1, tree);
    Idx[x] = idx ; 
    for (int const x_next: Adj[x]){
        if (x_next == Par[x]) continue;        
        idx ++;
        Par[x_next] = x;
        DFS(x_next, Par, Adj, tree, idx, Idx, depth+1, n);
        idx ++;
        upd_r(idx, depth, x, 2*n-1, tree);        
    }
}

void DFS_ans(int x, vector<int> Adj[], int Par[], int V[]){
    for(int x_next: Adj[x]){
        if (x_next != Par[x]){
            DFS_ans(x_next, Adj, Par, V);
            V[x] += V[x_next];
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);  
    int n, m, a, b, c, idx=0, Ia, Ib;
    cin >> n >> m;
    vector <int> Adj[n];
    int Tree[2*(2*n-1)][2];//for every node we keep the id of node and distance from root while visiting 
                        //that node using DFS. Using min-segment tree
    int Idx[n], Par[n];//parent of each node
    for (int i=0; i<n-1; i++){
        cin >> a >> b; 
        a--; b--;
        Adj[a].push_back(b);
        Adj[b].push_back(a);
    }
    Par[0]=-1; //root... does not have parent.
    DFS(0, Par, Adj, Tree, idx, Idx, 0, n);
    int V[n]={0};
    for(int i=0; i<m; i++){
        cin >> a >> b;    
        a--; b--;    
        Ia = Idx[a]; Ib = Idx[b];
        if (Ia>Ib) swap(Ia,Ib);
        c = min_r(Ia, Ib, 2*n-1, Tree);
        V[a]++; V[b]++; V[c]--; 
        if (c!=0) V[Par[c]]--;
    }
    
    DFS_ans(0, Adj, Par, V);
    for(int i=0; i<n; i++) cout << V[i] _space;
}