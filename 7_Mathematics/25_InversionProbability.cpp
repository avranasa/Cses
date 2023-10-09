#include <bits/stdc++.h>
using namespace std;
/*The problem is a bit unclear. Lets say in the given example with  "5 2 7" as input 
you get as a realization "3 2 1" then the number of inversions is 3. If you get "1 2 3"
then it is 0. */
signed main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int n, r, r_min, r_pairs;
    cin >>n ;
    vector <int> R;
    for(int i=0; i<n; i++){
        cin >> r;
        R.push_back(r);
    }
    
    double ans = 0.0, r_sum;
    for(int i=1; i<R.size(); i++){
        r_sum=0;
        for(int j=0; j<i; j++){
            r_min = min(R[i],R[j]);
            r_pairs = (r_min+1)*r_min /2 ;
            r_sum += r_min-r_pairs/(double)R[j];
        }
        ans += r_sum/(double)R[i];
    }  
    
    if (ans>0) ans -= 0.0000000000000001;//some precision issues ...(I have 0.920312500000000000021 instead of more accurate
                                        // 0.920312499999999970 in one example )    
    cout<<setprecision(6)<<fixed;
    cout<<ans;
}