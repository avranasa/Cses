#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, q, a, b, x, interval, i_;
    cin >> n >> q;
    int N_power2 = int( log2(n) );
    int X[N_power2+1][n];
    for (int i=0;i<n;i++){
        cin >> x;
        X[0][i]=x;
    }

    for (int row=1;row<=N_power2;row++){
        interval = 1 << (row-1);
        for (int i=0; i<n; i++){
            i_ = min(i+interval ,n-1);
            X[row][i] = min(X[row-1][i], X[row-1][i_]);
        }
    }

    for (int i=0; i<q; i++){
        cin >> a >> b; 
        interval = b-a+1;
        N_power2 = int( log2(interval));
        cout << min(X[N_power2][a-1], X[N_power2][b-(1<<N_power2)]) << endl;
    }
}