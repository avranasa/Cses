#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
#define int long long
using namespace std;
const long long inf = 1LL<<60; //1.5e18, max(long long)= 9e18 = 2^63
const int md = 1000000007;

pair<int,int> SumOfTwo(vector<int> & X, int i_st, int i_l, int Sq){
    //Returns the two indexes (smaller than i_l and bigger than i_l) to vector X that point to the
    //values whose sum is equal to Sq. If no such solution exists returns {-1,-1}. X should be sorted.
    int s;
    while (i_st<i_l){
        s=X[i_st]+X[i_l];
        if (s==Sq) return {i_st,i_l};
        else if (s<Sq) i_st++;
        else i_l--;
    }
    return {-1,-1};
}

signed main(){
    int n, a, S;
    vector<int> X, X_sorted;
    cin >> n >> S;
    for(int i=0; i<n; i++){
        cin >> a;
        X.push_back(a);
    }
    vector<size_t> Idx(X.size());
    iota(Idx.begin(), Idx.end(), 0);
    stable_sort(Idx.begin(), Idx.end(), [&X](size_t i1, size_t i2) {return X[i1] < X[i2];});
    for(auto i: Idx) X_sorted.push_back(X[i]); 
    pair<int,int> k;
    for(int i=0; i<n-2; i++){
        k = SumOfTwo(X_sorted, i+1, n-1, S-X_sorted[i]);
        if (k.first>-1){
            cout << Idx[i]+1 _space_ Idx[k.first]+1 _space_ Idx[k.second]+1;
            return 0;
        }
    }
    cout<< "IMPOSSIBLE";
    return 0;
}

