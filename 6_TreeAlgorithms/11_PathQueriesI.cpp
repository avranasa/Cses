/*You could solve it using Heavy-Light Decomposition like the "Path Queries II" problem.
The book proposes a different approach that is similar to the one I am doing here.
What I do here is based on the fact that the contribution of a node for the sum-operation 
can be nullified easily by adding its negative (the max-operation on the other hand is not
easy to nulify).
I do a DFS and whenever I find a unvisited node a append it in an array its value and when 
I return (i.e. visited all its children) I append the negative. The array is stored as a 
segment tree and the summation from the root to a node is the sum of all the element from 
the beginning till the point where the value of the node was inserted...
*/

#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '  
#define _space_ <<' '<<
#define int long long 
using namespace std;

int sum_range(int a, int b, int n, int tree[]){
    a+=n; b+=n;
    int s=0;
    while (a<=b) {
        if (a%2==1) s+=tree[a++];
        if (b%2==0) s+=tree[b--];
        a/=2; b/=2;
    }
    return s;    
}

void upd_range(int k, int x, int n, int tree[]){
    k += n;
    int add = x-tree[k];
    tree[k] += add;
    for (k/=2; k>=1; k/=2) tree[k]+=add;
}

void DFS(int x, int x_prev, vector<int> adj[], int tree[], int V[], int n, int &idx, int Idx[][2]){
    upd_range(idx, V[x], 2*n, tree);
    Idx[x][0] = idx++; 
    for(int const x_next:adj[x]){
        if (x_prev!=x_next) DFS(x_next, x, adj, tree, V, n, idx, Idx);
    }
    upd_range(idx, -V[x], 2*n, tree);
    Idx[x][1] = idx++; 
}


signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    int n, q, a, b, idx=0, t;
    cin >> n >> q;
    vector <int> adj[n];
    int V[n], Idx[n][2], tree[4*n]={0};//tree[4*n] because each node will be visited twice and the segment 
                    //tree needs double the memory, Idx[n][] points each node to the positions in the 
                    //array/segment-tree (the one positive and the one negative)
    for (int i=0; i<n; i++) cin >> V[i];
    for (int i=0; i<n-1; i++){
        cin >> a >> b; a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    DFS(0, -1, adj, tree, V, n, idx, Idx);

    for(int i=0; i<q; i++){
        cin >> t >> a; a--;
        if (t==1) {
            cin >> b;
            upd_range(Idx[a][0], b, 2*n, tree);
            upd_range(Idx[a][1], -b, 2*n, tree);
        }
        else cout << sum_range(0, Idx[a][0], 2*n, tree) _endl ;
    }
}