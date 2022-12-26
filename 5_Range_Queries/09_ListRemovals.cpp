// A second way to solve it is by using lists of elements and each element pointing not only
// to the immediate following element but also to the element that you have 2**i step forward
// with i taking all the integers values such that 2**i is not exceeding the list limits.
// When removing one element, let it be X, then all the previous elements that point to X 
// (with some distance 2**i) will have now to be updated and point (with the distance 2**i)
// to the next of X element. So each removal has complexity O(log n). The list should be 
// bi-directional so as easily to find with 2**i steps where you end up and also from where
// you end up to a specific element with 2**i steps

#include <bits/stdc++.h>
#define ff first
#define ss second
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
using namespace std;
const long long inf = 1LL<<60; //1.5e18, max(long long)= 9e18 = 2^63
const int md = 1000000007;

int sum(int a, int b, int n, int tree[]){
    a+=n; b+=n;
    int s =0;
    while (a<=b){
        if (a%2 == 1) s+= tree[a++];
        if (b%2 == 0) s+= tree[b--];
        a/=2; b/=2;
    }    
    return s;
}

void update(int pos, int x, int n, int tree[]){
    pos += n;
    tree[pos] = x;
    for (pos/=2; pos>=1; pos/=2) tree[pos] = tree[2*pos] + tree[2*pos+1];
}


void build(int n , int tree[]){
    //assumes that from pos n to 2*n the tree is initialized
    for (int i=n-1; i>0; i--) tree[i] = tree[2*i] + tree[2*i+1];
}


int BinarySearch(int tree[], int S, int n){
    //returns the index k for which the number of 1s in the range [0,k] is equal to S
    int a=0, b=n-1, k, S_curr;
    while(a<=b){
        k = (a+b)/2;
        S_curr = sum(0, k, n, tree);
        if (S_curr == S && tree[k+n]==1) return k;
        else if (S_curr < S) a=k+1;
        else b=k-1;
    }
    return 0;
}


int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);  
    int n, pos, actual_pos;
    cin >> n;
    int X[n], Tree_Active[2*n];
    for (int i=0; i<n; i++){
        cin >> X[i]; 
        Tree_Active[i+n] = 1;//The (i+n)-th is 1 if the i-th element of the input
                            // list is not yet removed. When removed it becomes 0.
    }
    build(n, Tree_Active);

    for (int i=0; i<n; i++){
        cin >> pos;
        actual_pos = BinarySearch(Tree_Active, pos, n);
        cout << X[actual_pos] _space;
        update(actual_pos, 0, n, Tree_Active);
    }
}