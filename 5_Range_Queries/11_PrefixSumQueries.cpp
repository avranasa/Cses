//Use two ranges structures. One that returns the sum of elements of range [0,a] and another 
//that gives you the index! of the maximum prefix sum (which is the same to sum [0,i], a<=i<=b)
//in range [a,b]
// Use segment trees
 
#include <bits/stdc++.h>
#define ff first
#define ss second
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
#define int long long
using namespace std;
const int md = 1000000007;
const int inf = 2e18;
 
 
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
 
 
int max(int a, int b, int n, int tree_max[], int tree_sum[]){
    int ans = 0, x, a_ = a;//! the empty range is considered as feasible solution with sum = 0 ?! So initialization ans=0.
    a+=n; b+=n;
    while (a<=b) {
        if (a%2==1) {
            x = sum(a_, tree_max[a], n, tree_sum);             
            a++;
            if (x>ans) ans = x;           
        }
        if (b%2==0) {
            x = sum(a_, tree_max[b], n, tree_sum);            
            b--;
            if (x>ans) ans = x; 
        }
        a/=2; b/=2;
    }
    return ans;    
}
 
 
void upd_sum(int k, int x, int n, int tree[]){
    k += n;
    int add = x-tree[k];
    tree[k] += add;
    for (k/=2; k>=1; k/=2) tree[k]+=add;
}
 
 
void upd_max(int k, int x, int n, int tree_max[], int tree_sum[]){
    tree_max[k+n] = k;
    k += n;
    int pos1, pos2, s1, s2;    
    for (k/=2; k>=1; k/=2) {
        pos1 = tree_max[2*k];
        pos2 = tree_max[2*k+1];
        s1 = sum(0, pos1, n, tree_sum);//the pos \in [a,b] that has max sum prefix in [a,b] 
        s2 = sum(0, pos2, n, tree_sum);//has also max sum prefix in [0,b]...
        tree_max[k] = (s1>s2) ? pos1 : pos2;
    }
}
 
 
signed main(){    
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    int n, q, x, a, b;
    cin >> n >> q;
    int tree_sum[2*n] = {0}, tree_max[2*n] = {0};
    for(int i=0; i<n; i++){
        cin >> x;
        upd_sum(i, x, n, tree_sum);
        upd_max(i, x, n, tree_max, tree_sum);
    }
 
    for(int i=0; i<q; i++){
        cin >> x >> a >> b;
        if (x==1){            
            upd_sum(a-1, b, n, tree_sum);
            upd_max(a-1, b, n, tree_max, tree_sum);
        }
        else{
            cout << max(a-1, b-1, n, tree_max, tree_sum) _endl;
        }
    }
 
}