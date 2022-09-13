#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <set>
using namespace std;

int main(){
    int n;
    long long x;
    vector <long long>  X;
    cin >> n;
    for (int i=0; i<n; i++){
        cin >> x;
        X.push_back(x);
    }
    sort(X.begin(), X.end());
    set <long long> MissingSum;//all the numbers smaller than MaxIntAttained that up till now haven't been the sum of a subset o
                                //the numbers we have already seen
    //set <long long> AttainedSum = {0}; YOU ACTUALLY DO NOT NEED IT... TAKES A LOT OF TIME!! TRY USING ONLY THE MissingSums
    long long MaxIntAttained=0;
    chrono::steady_clock::time_point begin, end;
    
    for (auto x: X){
        //begin = chrono::steady_clock::now();
        for(auto m: MissingSum){
            if (x>m){//all the upcoming x will be larger
                cout << m;
                return 0;
            }
            if (m+x>MaxIntAttained) MissingSum.insert(m+x);//must be before the next commands because here we didn't yet use x
            if (!MissingSum.count(m-x)) MissingSum.erase(m);//using x to achive the a sum equal to m
        }
        for(long long k=MaxIntAttained+1;k<x;k++ ) MissingSum.insert(k);//IF CHANGE FROM long long YOU DO IT int ->TIME LIMIT EXCEEDED
        MaxIntAttained += x;
    }
    if (MissingSum.empty()) cout<< MaxIntAttained+1;
    else cout << *MissingSum.begin();
}