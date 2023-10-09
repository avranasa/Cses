/*
I refer to amount of operation needed to have an increasing array as cost.
If you want to find the cost in the interval [a,b] where the initial values are 
[x_a, x_{a+1}, ..., x_b] and after you added the costs it becomes [y_a, y_{a+1},...]
with y_a <= y_{a+1} <= ... 
It holds cost([a,b]) = (y_a+y_{a+1}+...+y_b) - (x_a+x_{a+1}+...+x_b) . If you know that
x_c is the max of x in [a,b] then y_c==x_c and:
cost([a,b]) = (y_a+y_{a+1}+...+y_c) - (x_a+x_{a+1}+...+x_c) + (b-c)*x_c - (x_{c+1}+...+x_b) 
            = cost([a,n])-cost([c,n]) + (b-c)*x_c - (x_{c+1}+...+x_b) 
Denote that if 1<=a<=b<=c<=d<=n then the increased array on range [b,c]: [y_b,..., y_c]
has the same first elements as the increased array on range [b,d]: [y'_b,..., y'_c]
(i.e. y'_i = y_i for i \in [b,c]) but not with the increased array on range [a,c]: [y''_a, ... , y_c]
*/

#include <bits/stdc++.h>
#define ff first
#define ss second
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
#define int long long
using namespace std;
const int md = 1000000007;

int max_range(int a, int b, int n, int tree[][2]){
    //returns the position of the max value in the range [a,b]
    int ans=-1e8, k_max;
    a+=n-1; b+=n-1; //input & output of indexing assumed to start from 1;
    while (a<=b) {
        if (a%2==1) {
            if (tree[a][0]>ans){
                ans = tree[a][0]; 
                k_max = tree[a][1];
            }
            a++;
        }
        if (b%2==0) {
            if (tree[b][0]>ans){
                ans = tree[b][0];
                k_max = tree[b][1];
            }    
            b--;
        }
        a/=2; b/=2;
    }
    return k_max+1;  
}

void upd(int k, int x, int n, int tree[][2]){
    k += n-1; //input indexing assumed to start from 1;
    int k_max;
    tree[k][0]= x;
    tree[k][1]= k-n;
    for (k/=2; k>=1; k/=2) {
        k_max = (tree[2*k][0] > tree[2*k+1][0]) ? 2*k : 2*k+1;
        tree[k][0] = tree[k_max][0];
        tree[k][1] = tree[k_max][1];   
    }        
}

signed main(){ 
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    int n, q, i_next, a, b, i_max;
    cin >> n >> q;
    int X[n+1], S[n+1], I_next[n+1], Cost[n+2], tree_max[2*n][2];//tree_max finds the position of max value in a range 
                                                            //I_next points to the position of the next larger element
    S[0] = 0;
    for (int i=1; i<=n; i++) {
        cin >> X[i];
        S[i] = S[i-1] + X[i];
        upd(i, X[i], n, tree_max);
        }
    stack <int> Q;
    for (int i=n; i>0; i--){
        while ((!Q.empty()) && (X[i]>=X[Q.top()])) Q.pop();
        if (Q.empty()) I_next[i] = n+1;
        else I_next[i] = Q.top();
        Q.push(i);
    } 
    Cost[n+1] = 0;
    for (int i=n; i>0; i--){
        i_next = I_next[i];
        Cost[i] = Cost[i_next] + (i_next-1-i)*X[i] - (S[i_next-1]-S[i]);
    }

    for (int i=0; i<q; i++){
        cin >> a >> b;
        i_max = max_range(a, b, n, tree_max);
        cout << Cost[a] - Cost[i_max] + (b-i_max)*X[i_max] - (S[b]-S[i_max]) _endl;     
    }        
}
