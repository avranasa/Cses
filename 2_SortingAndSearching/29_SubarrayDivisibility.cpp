#include <bits/stdc++.h>
using namespace std;
 
int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    long int ans=0;
    int n, a, s=0;
    cin >> n ;   
    int  Mod_S[n]={0};//the i-th element of Mod_S counts how many subarrays
                // which start from the first given element has sum that
                // gives modulo_n equal to i
    Mod_S[0] = 1;
    for(int i=0; i<n; i++){
        cin >> a;
        s += a%n;
        if (s<0) s+=n;
        else if (s>=n) s-=n;
        ans += Mod_S[s];
        Mod_S[s] ++;
    }
    cout << ans;
}