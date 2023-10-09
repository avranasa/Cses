#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;  
#define ordered_set tree< pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag,tree_order_statistics_node_update> 
//multi set by changing above the less<int> to less_equal<int> => but I have troubles with erasing objects :-(
//check: https://www.geeksforgeeks.org/policy-based-data-structures-g/
  
int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    
    int n, k, med, WAY=1;
    cin >> n >> k;    
    int X[n];
    if (WAY==0){
        //using ordered statistics
        ordered_set S;
        for (int i=0; i<n; i++){
            cin >> X[i];
            S.insert({X[i],i});
            if (S.size()>=k) {
                if (S.size()==k+1) S.erase({X[i-k],i-k}); 

                med = (*S.find_by_order((k-1)/2)).first;
                cout << med << " ";
            }
        }
    }
    else if (WAY==1){
        //Much faster version... from 0.6 of Way=1 to 0.2 here
        //using two multiset S1,S2. Their union contains all the elements of the sliding window and
        //they are mutually exclusive. All elements of S1 are smaller than S2 and the median 
        //is *S1.rbegin(). S1 size is always bigger or equal to S2
        multiset <int> S1, S2;
        for(int i=0; i<n; i++){
            cin >> X[i];

            if (S1.size()==0) S1.insert(X[i]);
            else if (X[i]<*S1.rbegin()) S1.insert(X[i]);
            else S2.insert(X[i]);
            //Balancing
            if (S1.size()>1+S2.size()) {S2.insert(*S1.rbegin()); S1.erase(prev(S1.end()));}
            else if (S1.size()<S2.size()) {S1.insert(*S2.begin()); S2.erase(S2.begin());}

            if (S1.size()+S2.size()>=k){
                if (S1.size()+S2.size()==k+1){
                    if (X[i-k]<=*S1.rbegin()) S1.erase(S1.find(X[i-k]));
                    else S2.erase(S2.find(X[i-k]));
                    //Balancing
                    if (S1.size()>1+S2.size()) {S2.insert(*S1.rbegin()); S1.erase(prev(S1.end()));}
                    else if (S1.size()<S2.size()) {S1.insert(*S2.begin()); S2.erase(S2.begin());}
                }
                cout << *S1.rbegin()<< " ";
            }
        }
    }    
}