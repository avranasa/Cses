#include <iostream>

using namespace std;

int main(){
    int n, mod=1000000007;
    char c;
    cin >> n;
    int Grid[n+2][n+2]={};
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            cin >> c;
            if (c=='.') Grid[i][j]=0;
            else Grid[i][j]=-1;//a trap
        }
    }
    if (Grid[n][n]==-1 || Grid[1][1]==-1){
        cout << '0';
        return 0;
    }
    
    Grid[1][1]=1;
    for (int i=1; i<=n; i++){
        for (int j=1; j<=n; j++){
            if ((Grid[i][j]==-1) || (i==1 && j==1)) continue;
            Grid[i][j] = max(Grid[i-1][j],0) + max(Grid[i][j-1],0);
            Grid[i][j] %= mod;
        }
    }

    cout << Grid[n][n];
}