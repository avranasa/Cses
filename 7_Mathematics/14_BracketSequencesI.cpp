#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
#define int long long
using namespace std;
const int md = 1000000007;

int modpow(int x, int n, int p){
    int res=1; 
    x%=p;
    while(n>0){
        if (n%2) res= (res*x)%p; 
        n=n>>1; 
        x=(x*x)%p;
    }
    return res;
}

signed main(){
    int n, f1=1, f2_inv, f3_inv;
    cin >> n;
    if (n%2){
        cout << 0; 
        return 0;
    }
    //computing f1/(f2*f3) with f1=n!, f2=(n/2+1)!, f3=(n/2)!
    for (int x=1; x<=n; x++){
        f1 = (f1*x)%md;
        if (x==n/2) f2_inv=modpow(f1, md-2, md);
        if (x==n/2+1) f3_inv=modpow(f1, md-2, md);
    }
    cout <<((f1*f2_inv)%md * f3_inv)%md;
}