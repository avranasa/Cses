#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
using namespace std;
//const long long inf = 1LL<<60; //1.5e18, max(long long)= 9e18 = 2^63
const int md = 1000000007;

signed main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int a, b, min_m;
    cin >> a >> b;
    int X[500][500];
    if (a==b) {cout << 0 ; return 0;}
    else if (a>b) swap(a,b);//X[i][j]==X[j][i] so this swap does not change the answer
    for(int i=0; i<a; i++){
        for(int j=0; j<b; j++){
            if (i==j) X[i][j] = 0; 
            else if (i<j) {
                min_m = (i+2)*(j+2);
                for(int i_=0; i_<(i+1)/2; i_++) min_m = min(min_m, X[i_][j]+X[i-i_-1][j]+1);
                for(int j_=0; j_<(j+1)/2; j_++) min_m = min(min_m, X[i][j_]+X[i][j-j_-1]+1);
                X[i][j] = min_m;
                if (j<a) X[j][i] = min_m;//symmetry
            }
        }
    }
    cout << X[a-1][b-1];
}