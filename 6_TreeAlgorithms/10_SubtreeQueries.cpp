/*
I do a DFS and whenever I find a unvisited node a append it in an array its value and keep the size I1 of the array. 
When I return (i.e. visited all its children) I keep again the size of the array. If I want to compute the sum of all
the nodes of the subtree then I have to find the sum of the range of the array between I1 and I2...
*/

#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '  
#define _space_ <<' '<<
#define int long long 
using namespace std;

//segment tree
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

void upd_range(int k, int add, int n, int tree[]){
    k += n;
    tree[k] += add;
    for (k/=2; k>=1; k/=2) tree[k]+=add;
}


/*
//binary indexed tree
int sum(int k, int tree[]){
    int s = 0;
    while (k>=1){s += tree[k]; k -= k&-k;}
    return s;
}
int sum_range(int a, int b, int n, int tree[]){
    if (a==0) return sum(b+1, tree);
    else return sum(b+1, tree)-sum(a, tree);    
}

void upd_range(int k, int add, int n, int tree[]){
    k++;
    while (k<=n){
        tree[k] += add; 
        k += k&-k;
    }
}
*/

void DFS(int x, int x_prev, vector<int> adj[], int tree[], int V[], int n, int &idx, int Idx[][2]){
    upd_range(idx, V[x], n, tree);
    Idx[x][0] = idx++; 
    for(int const x_next:adj[x]){
        if (x_prev!=x_next) DFS(x_next, x, adj, tree, V, n, idx, Idx);
    }
    Idx[x][1] = idx-1; 
}


signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    int n, q, a, b, idx=0, t;
    cin >> n >> q;
    vector <int> adj[n];
    int V[n], Idx[n][2], tree[2*n]={0};//for sement tree you need memory [2*n] and for binary indexed tree [n]
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
            upd_range(Idx[a][0], b-V[a], n, tree);
            V[a] = b;
        }
        else cout << sum_range(Idx[a][0], Idx[a][1], n, tree) _endl ;
    }
}