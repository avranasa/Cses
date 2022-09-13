#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main(){
    int n, q, a, b;
    ll x;
    vector <ll> S{0};
    cin >> n >> q;
    for (int i=0;i<n;i++){
        cin >> x;
        S.push_back(S[i]+x);
    }
    for (int j=0;j<q;j++){
        cin >> a >> b;
        cout << S[b]-S[a-1]<<endl;
    }
}