#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
#define int long long
using namespace std;
const long long inf = 1LL<<60; //1.5e18, max(long long)= 9e18 = 2^63
const int md = 1000000007;

int power_mod(int a, int b, int mod_p){
    int ans;
    if ((b==0)||(a==1)) ans = 1;
    else if (a==0) ans = 0;
    else{
        ans = 1;
        while(b!=0){
            if (b%2==1) ans = (ans*a)%mod_p;
            a = (a*a)%mod_p;                
            b = b >> 1 ; //b = b/2;
        }
    }
    return ans;
}

signed main(){
    //CAREFUL: a^(b^c) != (a^b)^c
    // FERMAT LITTLE THEOREM necessary!
    ios::sync_with_stdio(0);
    cin.tie(0);  cout.tie(0);
    int n, a, b, c, a_b;
    cin >> n;
    for (int i=0; i<n; i++){
        cin >> a >> b >> c;     
        cout << power_mod(a, power_mod(b,c,md-1),md) _endl;   
    }
}
