#include <bits/stdc++.h>
#define ll long long
using namespace std;

void update(int k, ll diff, ll BinIdxTree[], int n){
    k++;
    while(k<=n){
        BinIdxTree[k-1] += diff;
        k += k & -k;
    }
}

ll sum(int k, ll BinIdxTree[]){
    k ++;
    ll ans = 0;
    while(k > 0){
        ans += BinIdxTree[k-1];
        k -= k & -k;
    }    
    return ans;
}

int main(){
    int n, q, a, b, choice, k;
    cin >> n >> q;
    ll x, prev_x=0, BinIdxTree[n]={}, diff;

    for (int i=0; i<n; i++){
        cin >> x;
        update(i, x-prev_x, BinIdxTree, n);
        // cout << "\n-----"<< x-prev_x;
        prev_x = x;
    }
    /*
    cout << endl << endl;
    for (auto i : BinIdxTree)  cout <<i << " " ;
    cout << endl;*/

    for (int i=0; i<q; i++){
        cin >> choice;
        if (choice == 1){
            cin >> a >> b >> diff;
            update(a-1, diff, BinIdxTree, n);            
            update(b, -diff, BinIdxTree, n);
        }
        if (choice == 2){
            cin  >> k;
            cout << sum(k-1, BinIdxTree) << endl;
        }
    }
}