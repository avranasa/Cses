//1st idea:
//The solution below is not adequate. One of the reasons is that assuming a pizzeria k
//serves the range k\in[a,b] and we increase the price p_k then how do can we compute
//the price at a point x\in[a,b]? A second problem is that if for example we decrease 
//a lot the price and the new range is [a_,b_] with a_<<a and b_>>b then we have somehow
//all the boundaries in ranges (a_,a] and [b,b_) to make them 0.
//You will have an array P[num_pizzerias] that saves the prices of each pizzeria.
//You will have an array B[n] that the sum(B[0:i]) is the pizzeria to which from
//position i you have to order... If B[i]>0 then it means that from position i 
//you order from a different pizzeria than position i-1...
//To find the "borders" of a pizzeria, i.e. within which area it serves, you could
//do a binary search on both sides of the pizzeria (left and with). With the binary
//search you find the exact position where it is preferable to buy from this pizzeria
//but not from any further position!

//2nd idea (seen from solution. Very smart!!! but works only if L1 penalty is assumed 
//for distance...)
//To find the cheapest pizzeria from k looking only on the left, i.e. pizzerias x<=k,
//you have to argmin_x{p_x - x + k} = argmin_x{p_x-x}. So because k is only a bias constant 
//it can ignored. So now you have to find the minimum in the range [1,k] of p_x-x...
//Repeat the same logic for the right side of x and then choose if the cheapest pizzeria is 
//on the right or left side.


#include <bits/stdc++.h>
#define ff first
#define ss second
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
using namespace std;
const int md = 1000000007;

int min_range(int a, int b, int n, int tree[]){
    a+=n; b+=n;
    int ans=tree[a];
    while (a<=b) {
        if (a%2==1) ans=min(ans,tree[a++]);
        if (b%2==0) ans=min(ans,tree[b--]);
        a/=2; b/=2;
    }
    return ans;    
}

void update(int k, int x, int n, int tree[]){
    k += n;
    tree[k] = x;
    for (k/=2; k>=1; k/=2) tree[k]=min(tree[2*k], tree[2*k+1]);
}

int main(){ 
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    int n, q, p, t, k;
    cin >> n >> q;
    int tree_l[2*n], tree_r[2*n];
    for (int i=0; i<n; i++){
        cin >> p;
        update(i, p+i, n, tree_r);
        update(i, p-i, n, tree_l);
    }
    for (int i=0; i<q; i++){
        cin >> t;
        if (t==1){//update pizza price
            cin >> k >> p; k--;
            update(k, p+k, n, tree_r);
            update(k, p-k, n, tree_l);
        }
        else{
            cin >> k; k--;
            cout << min(min_range(0, k, n, tree_l)+k, min_range(k, n-1, n, tree_r)-k) _endl;
        }
    }
}