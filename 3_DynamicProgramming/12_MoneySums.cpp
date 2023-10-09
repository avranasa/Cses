#include <bits/stdc++.h>
using namespace std;
//const long long inf = 1LL<<60; //1.5e18, max(long long)= 9e18 = 2^63
const int md = 1000000007;
 
int main(){
    //It is important to understand that the constraints n<=100 and x_i<=1000
    //makes the solution feasible. The maximum sum is 100*1000!
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int n, x, n_sums, x_new;
    cin >> n;
    vector <int> SumsInt; 
    bool SumsBool[100*1000+1]={false};
    for(int i=0; i<n; i++){
        cin >> x;
        n_sums = SumsInt.size();
        for (int j=0; j<n_sums; j++){
            x_new = x+SumsInt[j];
            if (SumsBool[x_new]) continue;
            SumsInt.push_back(x_new);
            SumsBool[x_new]=true;
        }        
        if (!SumsBool[x]) SumsInt.push_back(x);     
        SumsBool[x] = true;    
    }
    sort(SumsInt.begin(),SumsInt.end());
    cout << SumsInt.size()<< endl;
    for(auto & s: SumsInt) cout<<s <<" ";
}