#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
using namespace std;
#define int long long
const int md = 1000000007;

int modpow(int x, int k){
    //computes x^k mod md
    int res = 1;
    while(k>0){
        if (k%2) res = (res*x)%md;
        k/=2;
        x = (x*x)%md;
    }
    return res;
}


signed main(){
    //ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int n, ans, p;
    cin >> n;//Luckily n*n<=1e18 so using long long int for exponent can stil be accurate 

    ans = modpow(2, n*n);//no rotation
    p = (n%2==0) ? (n*n)/4 : (n*n)/4+1;
    ans += 2*modpow(2,p); //rotations 90 or 270 degrees
    p = (n%2==0) ? (n*n)/2 : (n*n)/2+1;//
    ans += modpow(2,p); //rotation 180 degrees
    ans %= md;
    int inv_n = modpow(4, md-2);//modulo inverse (... md is prime)
    cout << (ans*inv_n)%md;
}