#include <bits/stdc++.h>
#define int long long
using namespace std;
const int md = 1000000007;
 
signed main(){
    int n, f=1, s=0;
    cin >> n ;
    for(int k=n; k>1; k--){
        s = (k%2) ? s-f : s+f; //adding (-1)^k*(n!/k!)
        s %= md;    
        f=(f*k)%md;// finding f=n!/(k-1)!
    }
    if (s<0) s += md;
    cout << s;
}