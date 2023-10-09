#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
using namespace std;
#define int long long
const int md = 1000000007;
/*
Exactly k edges...=> powers of adjacency matrix are needed.
Sos: -the number of nodes is <100... i.e. small matrices...
     -directed graph
     -it is allowed two or more directed edges from node a to b
*/

vector<vector<int>> matmul_mod(vector<vector<int>> & A, vector<vector<int>> & B){
    //C=A@B ... all square matrices of same dimensions d
    int d = A.size();
    vector<vector<int>> C(d, vector<int> (d,0));
    for(int i=0; i<d; i++)
        for(int j=0; j<d; j++)
            for(int k=0; k<d; k++){
                C[i][j] += A[i][k]*B[k][j];
                C[i][j] %= md;
            }
                
    return C;
}


vector<vector<int>> matpow_mod(vector<vector<int>> A, int k){
    //returns res=A^k
    int d = A.size();
    vector<vector<int>> res(d, vector<int> (d,0));
    for(int i=0; i<d; i++) res[i][i] = 1;
    while(k>0){
        if (k%2) res = matmul_mod(res, A);
        k /= 2;
        if (k>0) A = matmul_mod(A,A);
    }
    return res;
}


signed main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int n, m, k, a, b;
    cin >> n >> m >> k;
    vector<vector<int>> Adj(n, vector<int> (n,0));
    for(int i=0; i<m; i++){
        cin >> a >> b; a--;b--;
        Adj[b][a] += 1; //There can exist two or more edges from a to b !
    }
    cout << matpow_mod(Adj, k)[n-1][0];
}