//I find this problem very similar to the sorting problem: "Nested Ranges Count"


//Create one array A that has 1 the first time a new distinct value appears and
//a second array B that for each values that appear multiple times it points to the
//next position of the array with the same value.
//Start processing the arrays in a sorted way. I.e if a1<a2 then you process 
//first the query concerning [a1,b1] and then [a2,b2]. Let's assume you have 
//answered for [a1,b1] and the next range is [a2,b2]. Check all the values x in 
//positions p_x \in [a1,a2). If an x appears also in some position "p=B[p_x]" 
//then do to A[p] = 1... The answer for query [a,b] is sum(A[a:b])...


#include <bits/stdc++.h>
#define ff first
#define ss second
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
//#define int long long
using namespace std;
const int md = 1000000007;

int sum(int a, int b, int n, int tree[]){
    a+=n; b+=n;
    int s=0;
    while (a<=b) {
        if (a%2==1) s+=tree[a++];
        if (b%2==0) s+=tree[b--];
        a/=2; b/=2;
    }
    return s;    
}

void add(int k, int x, int n, int tree[]){
    k += n;
    tree[k] += x;
    for (k/=2; k>=1; k/=2) tree[k]+=x;
}

int main(){    
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    int n, q, x, a, b, i_q=0;
    cin >> n >> q;
    int tree[2*n] ={0}, Ans[q], NextEq[n];//NextEq points to the next position with same value.
                                        //and if it does not exist such an element it is -1.
    
    unordered_map<int, int> Val2Idx;
    for (int i=0; i<n; i++){
        cin >> x;
        auto it = Val2Idx.find(x);
        if (it==Val2Idx.end()) {
            Val2Idx[x] = i;
            add(i, 1, n, tree);
        }
        else {
            NextEq[it->second] = i;
            it->second = i;
        }
        NextEq[i] = -1;
    }

    //storing and sorting the queries
    vector <pair<int, int>> Q;
    for (int i=0; i<q; i++){
        cin >> a >> b;
        Q.push_back({a-1,b-1});
    }    
    vector<size_t> idx(Q.size());
    iota(idx.begin(), idx.end(), 0);
    stable_sort(idx.begin(), idx.end(), [&Q](size_t i1, size_t i2) {return Q[i1] < Q[i2];});
        
    for (int i=0; i<n; i++){
        while( Q[idx[i_q]].ff==i ){
            Ans[idx[i_q]] = sum(Q[idx[i_q]].ff, Q[idx[i_q]].ss, n, tree);            
            i_q++;            
            if (i_q==q) break;
        }
        if (i_q == q) break;
        if (NextEq[i]!=-1) add(NextEq[i], 1, n, tree);
    }
    for (int i=0; i<q; i++) {cout << Ans[i] _endl;}

}
