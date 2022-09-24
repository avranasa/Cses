#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, q, x1, x2, y1, y2, s;
    char x;
    cin >> n >> q;
    int Forest[n+1][n+1]={};
    for (int i=1; i<=n; i++){
        for (int j=1; j<=n; j++){
            cin >> x;
            s = Forest[i][j-1] + Forest[i-1][j] - Forest[i-1][j-1];
            Forest[i][j] = s + int(x=='*') ;
        }
    }

    for (int i=0;i<q;i++){
        cin >> y1 >> x1 >> y2 >> x2;
        x1 --; y1 --;
        cout << Forest[y2][x2] + Forest[y1][x1] - Forest[y2][x1] - Forest[y1][x2] << endl;
    }
}