#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <numeric>
using namespace std;

int binarySearch(vector <int> &V, vector <int> &Idx, int x, int indx_start, bool &found){
    ///Returns the index (referred to Idx) of the equal or just greater than x
    int indx_end = V.size()-1, k;
    while (indx_start<=indx_end){
        k = indx_start + (indx_end-indx_start)/2;
        if (V[Idx[k]] == x){
            found = true;
            return k;
        }
        else if (V[Idx[k]] > x) indx_end = k-1;
        else indx_start = k+1;
    } 
    return -1;
}

int main(){
    int n, x, v, i_2nd_start;
    cin >> n >> x;
    vector <int> V, idx(n);
    for (int i=0; i<n; i++){
        cin >> v;
        V.push_back(v);
    }
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&V](int i1, int i2){return V[i1]<V[i2];});
    if ( (n==1) || (V[idx.end()[-1]] + V[idx.end()[-2]] < x) || (V[idx[0]] + V[idx[1]] > x) ) {
        cout << "IMPOSSIBLE";
        return 0;
    }
    //if (n>166895) cout << V[51057] <<" + "<< V[166895] <<" = "<<V[51057] +V[166895] <<endl;
      
    i_2nd_start = 1;
    bool found=false;
    for(int i=0; i<n-1; i++){
        i_2nd_start = binarySearch(V, idx, x-V[idx[i]], i+1, found);
        if (found){
            cout << idx[i_2nd_start]+1<< " " << idx[i]+1;
            return 0;
        }   
    }
    cout << "IMPOSSIBLE";
}
