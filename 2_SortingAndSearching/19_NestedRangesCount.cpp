// Bear in mind that if you have in positions 0 and 2 the [
// and in 4 and 6 the ] then inside an interval [1,5] it can 
// be either that the given intervals were [0,6] & [2,4] or
// [0,4] and [2,6] and the correct answer to the problem change 

// Also think of the edge cases where if you have 2*n brackets,
// then you have the first n brackets being [ and the rest being ].
// This can lead to have no pair of brackets being either included
// or include some other pair! Still you need a solution of
// O(n*logn) (<-not sure)

// If instead of asking each pair how many other pairs does it 
// include, it was asking each pairs which other pairs specifically
// does it include, then I think the necessary complexity would 
// grow to O(n^2)
#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace __gnu_pbds;

int main(){
    int n;
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
    int t = 0;// is used only to position "correctly" when ranges have at the same point the ]
    //Here I am using pair<int,int> inside the tree with pair.second to be the integer t. You can resolve 
    //correctly the equalities of ending brackets ] without using pairs & int. One way would be to create
    //a map that counts for each each point "x" where an ] will be inserted how many other ] have already been
    //inserted at  "x". Then use that information to correct the values of Contained[x] and Contains[x]
    
    
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
    

    for(int x: Contains) cout << x << " ";
    cout << endl;
    for(int x: Contained) cout << x << " ";

}