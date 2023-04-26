#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
#define int long long
using namespace std;
const int md = 1000000007;

int modpow(int x, int n, int m){
    int ans=1;
    x = x%m; 
    while(n>0){
        if (n%2==1) ans = (ans*x)%m;
        x = (x*x)%m;
        n = n>> 1; 
    }
    return ans;
}

    

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);  cout.tie(0);
    int n=0, f=1, ans;
    string s;
    getline(cin, s);
    map<char,int> C_f;
    for(char c: s){
        if (C_f.find(c)==C_f.end()) C_f[c] = 1;
        else C_f[c] ++;
        n++;
    }
    vector<int> fact={1,1}, invf={1,1};
    for(int i=2; i<=n; i++){
        f = (f*i) % md;
        fact.push_back(f);
        invf.push_back(modpow(f, md-2, md));        
    }
    ans = fact[n];
    for(auto const & [c,f]: C_f){
        ans = (ans*invf[f])% md;
    }
    cout << ans;
}