#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
#define int long long
using namespace std;
const long long inf = 1LL<<60; //1.5e18, max(long long)= 9e18 = 2^63
const int md = 1000000007;

signed main(){
    int n, a, d, R=0, t=0;
    vector <int> A, D, Idx;
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> a>> d;
        A.push_back(a); 
        D.push_back(d);
        Idx.push_back(i);
    }
    
    sort(Idx.begin(), Idx.end(), [&A](int i1, int i2){return A[i1]<A[i2];});
    for(int i: Idx) {
        t += A[i];
        R += D[i] - t;
    }
    cout << R;
}