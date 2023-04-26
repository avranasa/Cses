#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
#define int long long
using namespace std;
const int md = 1000000007;
/*
int modpow(int x, int n, int m){
    //computes (x^n)mod m
    if (n==0) return 1;
    int v = modpow(x,n/2,m);
    v = (v*v) % m;
    if (n%2==1) v=(v*x) % m;
    return v;
}
*/

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
    ios::sync_with_stdio(0);
    cin.tie(0);  cout.tie(0);
    int n, a, b, f;
    cin >> n;
    vector <int> F={1,1}, invF={1,1};
    for (int x=2; x<1000001; x++){
        f =  (F.back() * x )% md;   
        F.push_back(f);
        invF.push_back(modpow(f,md-2,md));
    }

    for (int i=0; i<n; i++){
        cin >> a >> b;
        cout << (((F[a]*invF[b])%md)*invF[a-b])% md _endl;
    }    
}