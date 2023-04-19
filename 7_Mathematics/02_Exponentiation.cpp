#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
#define int long long
using namespace std;
const long long inf = 1LL<<60; //1.5e18, max(long long)= 9e18 = 2^63
const int md = 1000000007;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);  cout.tie(0);
    int n, a, b, ans;
    cin >> n;
    for (int i=0; i<n; i++){
        cin >> a >> b;
        if ((b==0)||(a==1)) ans = 1;
        else if (a==0) ans = 0;
        else{
            ans = 1;
            while(b!=0){
                if (b%2==1){
                    ans = (ans*a)%md;
                }
                //a = a % md;
                a = (a*a)%md;                
                b = b >> 1 ; //b = b/2;
            }
        }   
        cout << ans _endl;    
    }
}
