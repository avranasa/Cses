// using the code of 19_NestedRangesCount.cpp. Check that file for more information and comments
#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace __gnu_pbds;

int main(){
    int n, t=0;
    cin >> n;
    int OpenBr[n], ClosedBr[n], Contains[n], Contained[n];    
    for (int i=0; i<n; i++)  cin >> OpenBr[i] >> ClosedBr[i];


    vector <int> idx(n); //will keep the ranges in asceding order with respect to the [
    iota(idx.begin(), idx.end(), 0); 
    stable_sort(idx.begin(), idx.end(), [&OpenBr, &ClosedBr](int i1, int i2) {
        if (OpenBr[i1] != OpenBr[i2])   return OpenBr[i1] < OpenBr[i2];
        else   return ClosedBr[i1] > ClosedBr[i2]; //SOS! first put the range that can/may contain the other
        });
    tree< pair<int,int>, null_type, less<pair<int,int>>, rb_tree_tag, tree_order_statistics_node_update>  ordered_set;
    
    for(int i: idx){
        //each bracket that is considered to be inserted in the ordered_set can only be 
        //contained by the ranges already in the ordered_set (and not of the rest of the ranges)
        ordered_set.insert( {ClosedBr[i], --t} ); //In case of other already inserted elements having the 
        // same value with ClosedBr[i], this element should be inserted in the SMALLEST possible index (hence --t)
        Contained[i] = ordered_set.size() - ordered_set.order_of_key({ClosedBr[i],t}) -1 ;
    }


    reverse(idx.begin(), idx.end());
    ordered_set.clear();
    for(int i: idx){
        //each bracket that is considered to be inserted in the ordered_set can only contains
        //the ranges already in the ordered_set (and not of the rest of the ranges)
        ordered_set.insert({ClosedBr[i], ++t});//In case of other already inserted elements having the 
        // same value with ClosedBr[i], this element should be inserted in the BIGGEST possible index  (hence ++t)
        Contains[i] = ordered_set.order_of_key({ClosedBr[i],t}) ;
    }
    

    for(int x: Contains) cout << ((x>0)? 1:0) << " ";
    cout << endl;
    for(int x: Contained) cout << ((x>0)? 1:0) << " ";

}