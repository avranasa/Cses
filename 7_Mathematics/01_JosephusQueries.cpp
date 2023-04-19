#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
//#define int long long
using namespace std;
const long long inf = 1LL<<60; //1.5e18, max(long long)= 9e18 = 2^63
const int md = 1000000007;

int onecycle_josephus(int n, int k, int i_st, int k_r, int jump){
    //n is the number of children are left in this cycle
    //k_r are the number of children already removed in previous cylces
    //k is the query (which will be the k-th child to be removed)
    //i_st is the position of the first child
    //If you remove the j-th child then j+jump will be the next to 
    //be removed excluding the ones already removed
    //A cycle is when the index of the next child to be removed is 
    //bigger than (n-1) (using 0 indexing) and so we start from the 
    //beginning.
    //Returns the index of the (k-k_r) child to be removed
    int k_r_max = (n-i_st-1)/jump+1;
    if (k_r+k_r_max>=k){
        //no more cycles needed
        return (k-k_r-1)*jump + i_st;
    }
    
    int i_end = i_st+(k_r_max-1)*jump, i_ans, n_new=n-k_r_max;
    int i_st_new = ((i_end+jump)%n )%n_new;//the %n_new is added in case (i_end+jump)%n >= n_new
    i_ans = onecycle_josephus(n_new, k, i_st_new, k_r+k_r_max, jump);
    if (i_ans<i_st) return i_ans;
    else return i_ans+(i_ans-i_st)/(jump-1)+1;
}


signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);  cout.tie(0);
    int q, k, n, i_st, jump=2;
    cin >> q;
    for(int i=0; i<q; i++){
        cin >>n >> k;
        i_st = (jump-1)%n; // the %n is for the case that jump-1 >= n
        cout << onecycle_josephus(n, k, i_st, 0, jump) + 1 _endl;
    }
}




