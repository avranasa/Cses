#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
#define int long long
using namespace std;
const int md = 1000000007;
/*
We want the combinations (not permutation).
... to solve it you assume that for n=0 the answer is f(0)=1, and so the initial vector
is [f(0), f(-1), ..., f(-5)] = [1, 0, ..., 0].... therefore the answer is A^n[0][0]...
*/

vector<vector<int>> matmul(vector<vector<int>> & A, vector<vector<int>> & B){
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

vector<vector<int>> modpow_mat(vector<vector<int>> A, int n){
    //returns A^n
    int d = A.size();
    vector<vector<int>> res(d, vector<int> (d,0));
    for(int i=0; i<d; i++) res[i][i]=1; //eye matrix
    while(n>0){
        if (n%2==1) res = matmul(res, A);
        n /= 2;
        if (n>0) A = matmul(A, A);
    }
    return res;    
}

signed main(){    
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    vector<vector<int>> A { { 1, 1, 1, 1, 1, 1 },
                            { 1, 0, 0, 0, 0, 0 },
                            { 0, 1, 0, 0, 0, 0 },
                            { 0, 0, 1, 0, 0, 0 },
                            { 0, 0, 0, 1, 0, 0 },
                            { 0, 0, 0, 0, 1, 0 }  };

    int n;
    cin >> n;
    cout << modpow_mat(A,n)[0][0];
}