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
In the test problems assumes that the final answer will not be greater than what a long long int 
can express... this holds because even if k=10^9 and all edges are with weight 10^9 the total cost
will be 10^18 which is less than the max of long long int 
*/

vector<vector<int>> mat_min_mul(vector<vector<int>> & A, vector<vector<int>> & B){
    //C=A@B ... all square matrices of same dimensions d
    int d = A.size();
    vector<vector<int>> C(d, vector<int> (d,-1));
    for(int i=0; i<d; i++)
        for(int j=0; j<d; j++)
            for(int k=0; k<d; k++){
                if ((A[i][k]!=-1)&&(B[k][j]!=-1)) C[i][j] = (C[i][j] == -1) ? A[i][k]+B[k][j] : min<int>(C[i][j], A[i][k]+B[k][j]);
            }
                
    return C;
}


vector<vector<int>> mat_min_pow(vector<vector<int>> A, int k){
    //returns res=A^k
    int d = A.size();
    vector<vector<int>> res(d, vector<int> (d,-1));//Sos: Be careful of the initialization !!!
    for(int i=0; i<d; i++) res[i][i] = 0; //            and what is the "unit" matrix ...
    while(k>0){
        if (k%2) res = mat_min_mul(res, A);
        k /= 2;
        if (k>0) A = mat_min_mul(A,A);
    }
    return res;
}


signed main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int n, m, k, a, b, c;
    cin >> n >> m >> k;
    vector<vector<int>> Adj(n, vector<int> (n, -1));
    for(int i=0; i<m; i++){
        cin >> a >> b >> c; a--;b--; 
        Adj[b][a] = (Adj[b][a]==-1) ? c : min<int>(Adj[b][a], c); //There can exist two or more edges from a to b !
    }

    cout << mat_min_pow(Adj, k)[n-1][0];
}