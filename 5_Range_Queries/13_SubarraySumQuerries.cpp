//Create a segment tree and for each range [a,b] store 1) the sum or range [a,b],
//2)the max sum of array [a,c] (c<=b) 3)the max sum of array [c,b] (c>=a) and,
//4)max sum of array [c,d] with a<=c<=d<=b.
//NOTE: Empty array counts have a sum 0!
 
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
 
 
void update(int k, int x, int n, int tree[][4]){
    k += n;
    tree[k][0] = x;
    tree[k][1] = tree[k][2] = tree[k][3] = max<int>(x,0);
    for (k/=2; k>=1; k/=2) {
        tree[k][0] = tree[2*k][0] + tree[2*k+1][0];
        tree[k][1] = max<int>(tree[2*k][1], tree[2*k][0]+tree[2*k+1][1]);
        tree[k][2] = max<int>(tree[2*k+1][2], tree[2*k][2]+tree[2*k+1][0]);
        tree[k][3] = max<int>({tree[2*k][3], tree[2*k+1][3], tree[2*k][2]+tree[2*k+1][1]});
    }
}
 
signed main(){ 
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    int n_tree = 1, n, m, x, k;
    cin >> n >> m;
    while (n_tree < n) n_tree *= 2;// use a complete binary tree... n should be power of 2
    int tree[2*n_tree][4]={0};
    for (int i=0; i<n; i++){
        cin >> x;
        update(i, x, n_tree, tree);
    }
    for (int i=0; i<m; i++){
        cin >> k >> x;
        update(k-1, x, n_tree, tree);
        cout << tree[1][3] _endl;
    }
}