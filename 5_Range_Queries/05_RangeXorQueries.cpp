#include <bits/stdc++.h>
using namespace std;

int main(){
    //important property: (a ^ b) ^ a = b
    int n, q, a, b, x;
    cin >> n >> q;
    int XorSum[n+1];
    XorSum[0]=0;
    for (int i=1;i<=n;i++){
        cin >> x;
        XorSum[i] = XorSum[i-1] ^ x;
    }
    for (int i=0; i<q; i++){
        cin >> a >> b;
        cout << (XorSum[b] ^ XorSum[a-1]) << endl;
    }
}