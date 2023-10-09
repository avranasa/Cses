//Previous version passes the test but it is relatively slow (0.86sec). Even though I could do some 
//optimization to imporve performance, here I implement an algorithm that is faster.
//The algorithm uses segment trees again and the idea is that if you have two ranges [a,b], [b+1,c]
//and for each segment you know the sums of the all the elemnt of each range and also their maximum
//prefix sums then you can compute the sum of the range [a,c] as well as its maximum sum prefix.
//Quite faster than previous version (0.14 instead of 0.86)
//Be careful with the segment tree. To be sure that the range corresponding to tree[2*k] is a contiguous
//range [a,b] and that tree[2*k+1] is also a contiguous range [b+1,c] (given that 2*k is not some power of 2 
//minus 1), we force n, i.e. number of stored elements, to be equal to a power of 2.

#include <bits/stdc++.h>
#define ff first
#define ss second
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
#define int long long
using namespace std;
const int md = 1000000007;
 
int max_pref_sum(int a, int b, int n, int tree[][2]){
    int max_pr_l = 0, max_pr_r = 0;
    int s_l=0, s_r=0;//! the empty range is considered as feasible solution with sum = 0 ?! So initialization s_l=s_r=0
    a+=n; b+=n;
    while (a<=b) {
        if (a%2==1) {
            max_pr_l = max<int>(s_l+tree[a][1], max_pr_l);
            s_l += tree[a][0];            
            a++;
        }
        if (b%2==0) {
            max_pr_r = max<int>(tree[b][0]+max_pr_r, tree[b][1]);      
            b--;
        }
        a/=2; b/=2;
    }
    int ans = max<int>(s_l+max_pr_r, max_pr_l);
    return ans;    
}

void upd(int k, int x, int n, int tree[][2]){
    k += n;
    tree[k][0] = x;
    tree[k][1] = max<int>(x,0);
    for (k/=2; k>=1; k/=2) {
        tree[k][0] = tree[2*k][0] + tree[2*k+1][0];
        tree[k][1] = max<int>(tree[2*k][1],tree[2*k][0] + tree[2*k+1][1]);//n is a power of 2 which assures that tree[2*k]
            //corresponds to a contiguous range which is on the left of the one corresponding to tree[2*k+1]
    }
}

 
signed main(){    
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    int n, n_, q, x, a, b;
    cin >> n_ >> q;
    n = 1;
    while (n<n_) n *= 2;// use a complete binary tree... n should be power of 2
    int tree[2*n][2] = {0};//first column is the same of the corresponding range
                            //and second of its maximum prefix sum
    for(int i=0; i<n_; i++){
        cin >> x;
        upd(i, x, n, tree);   
    }
    
    
    for(int i=0; i<q; i++){
        cin >> x >> a >> b;
        if (x==1){            
            upd(a-1, b, n, tree);
        }
        else{
            cout << max_pref_sum(a-1, b-1, n, tree) _endl;
        }
    }
 
}