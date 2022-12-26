#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
#define int long long
using namespace std;
const long long inf = 1LL<<60; //1.5e18, max(long long)= 9e18 = 2^63
const int md = 1000000007;

signed main(){
    int n, T = 0, max_t = 0, t;
    cin >> n;
    for (int i=0; i<n; i++){
        cin >> t;
        max_t = max( max_t, t);
        T += t;
    }
    cout << max(2*max_t, T);
}

//Rank I have now on the site 2917