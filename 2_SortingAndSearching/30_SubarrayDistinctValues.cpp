#include <bits/stdc++.h>
using namespace std;

int main(){
    long int ans = 0;
    int n, k, i=-1, WAY = 2;
    cin >> n >> k;        
    int X[n];
    if (WAY == 1){
        unordered_set <int> S;//keeps the distinct elements of the subarray from
                          //i+1 element to j
        unordered_map<int, int> Freq;//for all the distinct elements of S it tracks their frequency
        for(int j=0; j<n; j++){
            cin >> X[j];
            if (S.count(X[j])==0) {
                S.insert(X[j]);
                Freq[X[j]] = 1;           
                if (S.size()==k+1){
                    for(i=i+1; i<j; i++){
                        Freq[X[i]]--;
                        if (Freq[X[i]]==0) break;
                    }
                    S.erase(X[i]);
                }  
            } 
            else Freq[X[j]]++;
            ans += j-i;
        }
    }
    else if (WAY==2){
        //similar to the previous way without using the data structure "set". Slightly faster
        int k_run = 0;
        unordered_map<int, int> Freq;//for all the distinct elements of S it tracks their frequency
                        //unordered makes reduces time from 0.34 to 0.19
        for(int j=0; j<n; j++){
            cin >>  X[j];
            auto it = Freq.find(X[j]);
            if (it == Freq.end())  it = Freq.insert(it, {X[j],0});
            if (it->second==0){
                if (k_run==k){
                    for(i=i+1; i<j; i++){
                        Freq[X[i]]--;
                        if (Freq[X[i]]==0) break;
                    }
                }
                else k_run++;
            }
            it->second ++;
            ans += j-i;
        }
    }    
    cout << ans;
}