#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
#define int long long
using namespace std;
const int md = 1000000007;

void mod_mat_mul(int A[2][2],int B[2][2], int C[2][2], int k){
    //C=A@B
    int a,b,c,d;
    a = (A[0][0]*B[0][0] + A[0][1]*B[1][0])%k;
    b = (A[0][0]*B[0][1] + A[0][1]*B[1][1])%k;
    c = (A[1][0]*B[0][1] + A[1][1]*B[1][1])%k;
    d = (A[1][0]*B[0][0] + A[1][1]*B[1][0])%k;
    C[0][0] = a; C[0][1] = b; C[1][1] = c; C[1][0] = d;
}

void modpow_mat(int A[][2], int n, int k){
    int res[2][2]={{1,0},{0,1}};
    while(n>0){
        if (n%2==1) mod_mat_mul(res, A, res, k);
        n /= 2;
        mod_mat_mul(A, A, A, k);
    }
    for(int i=0;i<2;i++) for(int j=0;j<2;j++) A[i][j]=res[i][j];    
}

signed main(){
    int n, A[2][2]={{0,1},{1,1}};
    cin >> n;
    modpow_mat(A, n, md);
    cout << A[0][1];
}