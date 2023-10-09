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

int gcd(int a, int b){
    //if (a<b) swap(a,b);
    if (b==0) return a;
    return gcd(b, a%b);
}

vector<int> gcd_vec(int n){
    //returns a vector of lengh n that the i-th element is equal to gcd(n,i)
    vector<int> gcd_v(n,1);
    gcd_v[0] = n; gcd_v[1] = 1;
    for(int i=2; 2*i<n; i++){
        if (n%i != 0) continue;
        int x = i/gcd_v[i];
        for (int k=i; k<n; k+=i)
            gcd_v[k] *= x;
    }
    return gcd_v;
}

signed main(){
    //ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int n, m, ans=0, p, WAY = 2;
    cin >> n >> m;

    if (WAY == 1){
        for(int k=0; k<n; k++) ans = (ans+modpow(m,gcd(n,k)))%md;
    }
    else{    //5.5 times faster
        auto v = gcd_vec(n);
        map<int, int> freq;
        for (auto x: v){
            if (freq.count(x)==0) freq[x]=1;
            else freq[x] ++;
        } 
        for (auto & x : freq) {
            p = modpow(m,x.first)%md;
            p = (x.second*p) %md;
            ans = (ans+p) % md;
        }
    }   
    
    int inv_n = modpow(n, md-2);//modulo inverse (... md is prime)
    cout << (ans*inv_n)%md;
}