// BAD exercise because you lose time with overflow stupidities that in the version of C++ of my local pc the overflow is detected 
// by the function isOverflow but on the cses site it does not
// Using the logarithms works both locally and on the site.

#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
#define int long long
using namespace std;
const long long inf = 1LL<<62; //4.5e18, max(long long)= 9e18 = 2^63
const int md = 1000000007;

bool isOverflow(int a, int b){
    // Check if either of them is zero
    if (a == 0 || b == 0)  return false;  
    int res = a * b;
    if (a == res / b)  return false;
    else   return true;
}
 

signed main(){
    int n, k;
    cin >>n >> k;
    vector <int> A(k);
    for (int i=0; i<k; i++) cin >> A[i];
    int ans = 0, x, sing ;
    bool add = true;
    for(int i=1; i< (1<<k); i++) {
        x = 1;
        sing = -1;
        add = true;
        for(int pos=0; pos<k; pos++){
            if (i & (1<<pos)){
                //if (isOverflow(x,A[pos]) || x*A[pos]>n){  add = false;  break; }   //<=Gives on the site WRONG results... but locally correct!!!
                if (log(x)+log(A[pos]) > log(n))   {  add = false;  break; }   //<=Gives on the site correct results
                x *= A[pos];
                sing *= -1; 
            }
        }        
        if (add) ans = ans + sing* (n/x);
    }
    cout << ans;
}
