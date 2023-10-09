#include <bits/stdc++.h>
using namespace std;
 
signed main(){
    int n, x;
    cin >> n;
    vector <int> V; //If the i-th element is x, it means that the minimum  
                    //last value of a subsequence of length (i+1) is x.
    for (int i=0; i<n; i++){
        cin >> x;
        auto idx = lower_bound(V.begin(), V.end(), x);
        if (idx == V.end()) V.push_back(x);
        else *(idx) = x;
    }
    cout << V.size();
}