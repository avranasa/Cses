#include <bits/stdc++.h>
#define ll long long
using namespace std;

void update(int k, ll Dx, ll tree[], int n){
    //indexing k assuming indexing of array starts from 1
    //Dx -> how much to increase the k-th element
    while(k<=n){
        tree[k-1] += Dx;
        k += k & -k; 
    }    
}

ll sum(int a, int b, ll tree[]){
    //sum of range [a,b] with indexing of array starting from 1
    ll s_a=0, s_b=0;
    a --; //to include X[a] in the sum ... 
    while (a>0) {
        s_a += tree[a-1];
        a -= a & -a;
    }
    while (b>0) {
        s_b += tree[b-1];
        b -= b & -b;
    }
    return s_b - s_a;
}

int main(){
    int n, q, option, a, b, k;
    cin >> n >> q;
    ll x, X[n], tree[n]={};
    for(int i=1; i<=n; i++){
        cin >> x;
        update(i, x, tree, n);
        X[i-1] = x;
    }
    
    for(int i=0; i<q; i++){
        cin >> option;
        if (option == 1){
            cin >> k >> x;
            update(k, x- X[k-1], tree, n);
            X[k-1] = x;
        }
        else if (option == 2) {
            cin >> a >> b;
            cout << sum(a,b,tree) << endl;
        }      
    }

}
