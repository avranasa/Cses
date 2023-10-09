#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
#define int long long
using namespace std;
const int md = 1000000007;

int modpow(int x, int n, int p){
    int ans=1; 
    x %= p;
    while(n>0){
        if (n%2==1) ans = (ans*x)%md;
        n /= 2;
        x = (x*x)%md;
    }
    return ans;
}


signed main(){
    int n, m, f1=1, f2_inv, f3_inv;
    cin >> n >> m;
    // finding (n+m-1)! / (m!(n-1)!)
    for(int i=1; i<n+m; i++){
        f1 = (f1*i) % md;
        if (i==m) f2_inv = modpow(f1, md-2, md);
        if (i==n-1) f3_inv = modpow(f1, md-2, md); 
    }
    cout << ((f1*f2_inv)%md * f3_inv)%md;
}