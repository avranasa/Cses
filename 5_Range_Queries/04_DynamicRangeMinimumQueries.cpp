#include <bits/stdc++.h>
using namespace std;
 
int min_in_range(int n, int Data[], int a, int b){
    a += n; b += n;
    int ans = Data[a];
    while (a<=b){
        if (a%2==1) ans = min(ans, Data[a++]);
        if (b%2==0) ans = min(ans, Data[b--]);
        a/=2; b/=2;
    }
    return ans;
}
 
void update_structure(int k, int v, int n, int Data[]){
    k += n;
    Data[k] = v;
    for (k/=2; k>0; k/=2)  Data[k] = min(Data[2*k],Data[2*k+1]);
}
 
int main(){
    int n, q, v, a, b, c, k;
    cin >> n >> q;
    int Data[2*n];
    for(int i=0; i<n; i++){
        cin >> v;
        update_structure(i, v, n, Data);
    }
 
    for(int i=0; i<q; i++){
        cin >> c;
        if (c==1){
            cin >> k >> v;
            update_structure(k-1, v, n, Data);
        }
        if (c==2){
            cin >> a >> b;
            cout << min_in_range(n, Data, a-1, b-1) << endl;
        }
    }
}