#include <bits/stdc++.h>
using namespace std;
#define int long long
//const long long inf = 1LL<<60; //1.5e18, max(long long)= 9e18 = 2^63
//const int md = 1e9+7;
const int md = 1000000007;
 

signed main(){
    int N, d_max, d_max_prev, d1, d2;
    //int A[501][500*501/4+5];//A[n,d] is equal to the number of ways you can split the set S={1,2,...,n} into two mutually
                // exclusive subsets S1,S2 such that their sum of elements differ by d (i.e. sum(S1)-sum(S2)=d ...)
                // It holds A[n,d] = A[n-1,abs(n-d)] + A[n-1,n+d] and the maximum d that we may considered should be
                // less or than N*(N+1)/2/2 since we search A[N,0]...
    //int A[2][500*501/2+5] = {0}; //same logic but more memory efficient by using n%2 instead of n...
    
    cin >> N;
    int A[2][500*501/4+5] = {0};
    if (((N+1)*N)%4 != 0) { cout << 0; return 0; }
    A[1][1] = 1, d_max_prev = 1;
    for(int n=2; n<=N; n++){
        d_max = min(n*(n+1)/2, N*(N+1)/4);
        for(int d=0; d<=d_max; d++){
            d1 = abs(n-d);
            d2 = n + d;
            A[n%2][d] = A[(n-1)%2][d1];     
            if (d2<=d_max_prev) A[n%2][d] += A[(n-1)%2][d2];
            A[n%2][d] %= md;
        }  
        d_max_prev = d_max;    
    }
    //cout << A[N%2][0]/2; //THIS IS ALMOST CORRECT... IF NOT FOR %MD!!!
         // Careful when dividing and you give the answers in modulo md
    cout << A[(N-1)%2][N];
}
