#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
#define int long long
using namespace std;
const long long inf = 1LL<<60; //1.5e18, max(long long)= 9e18 = 2^63
const int md = 1000000007;

int sum_interval(int & A, int & B, int & m){
    // if instead of calling with reference the variables... i.e. int A instead of int & A it runs two times slower!!!
    // Returns the modulo m of the sum of all numbers from A to B.     
    int s, s_A, s_B ;
    //s = ((B*(B+1))/2 - (A*(A-1))/2)%md; // since A,B can be of order 10^12 B*(B+1) can be of order 
                                        // 10^24 and long long int goes till 9e18 approximately...so this 
                                        // version may give wrong results....
    if (B%2==0) s_B = ((B/2)%m)*((B+1)%m);
    else s_B = (B%m)*(((B+1)/2)%m);            
    if (A%2==0) s_A = ((A/2)%m)*((A-1)%m);
    else s_A = (A%m)*(((A-1)/2)%m);
    s =  (s_B%m - s_A%m )%m; 
    if (s<0) s += m; // the +m is to avoid negative numbers
    return s;
}

signed main(){
    int WAY = 3;
    int n, ans;
    cin >> n;
    if (WAY==1){
        ans = 0;
        for(int k=1; k<=n; k++)  {
            ans += (k*(n/k))%md;
            ans %= md;
        }
    }    
    if (WAY==2){
        //slightly faster... 
        int f=1,m=md;
        ans = sum_interval(f, n, m); //summing all numbers from 1 to n;
        ans %= md;
        int stop_n = n;
        for(int k=1; k<=n; k++)  {
            ans += (k*(n/k -1 ))%md;// the -1 because you included k as a "self factor"...
            ans %= md;
            if (n/k-1==0) break;
        }
    }
    if (WAY==3){
        ans = 0;
        int A=1, B, r=n, s, s_B, s_A, m=md;
        while (r>=1){
            //All numbers k\in[A,B] are all the numbers such that floor(n/k) equals to r.
            if (r==1) B=n;
            else B = n/r;
            s = sum_interval(A, B, m);
            ans = (ans + r*s)%md;
            A = B+1;
            r = n/A;
        }
    }
    cout << ans;
}
    