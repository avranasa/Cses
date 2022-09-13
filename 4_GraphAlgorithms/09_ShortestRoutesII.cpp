#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define INF 4e18//9e18 is the max

int main(){
    int n,m,a,b,q;
    ll c, dist_through_k, k;
    cin >> n >> m >> q;
    ll Dist[n][n];
    for (int i=0;i<n;i++) for (int j=0;j<n;j++) Dist[i][j] = INF; 
    //for (int i=0;i<n;i++) Dist[i][i]=0; //<-- not necessary if you avoid k==a or k==b...
    for (int i=0;i<m;i++){
        cin >> a >> b >> c;
        Dist[a-1][b-1] = min(c,Dist[a-1][b-1]);
        Dist[b-1][a-1] = min(c,Dist[a-1][b-1]);  
    }

    for (int k = 0; k<n; k++){
        for(a=0; a<n; a++){
            if (a==k) continue;
            for(b=a+1; b<n; b++){// you can start from a+1 since the graph is not directed
                if (b==k) continue;
                dist_through_k = Dist[a][k] + Dist[k][b];
                if (Dist[a][b]>dist_through_k){
                    Dist[a][b]=dist_through_k;
                    Dist[b][a]=dist_through_k;
                }
            }
        }
    }

    vector <pair <int,int>> Q;
    for (int i=0;i<q;i++){
        cin >> a >> b;
        Q.push_back({a-1,b-1});
    }
    for (int i=0;i<q;i++){
        tie(a,b) = Q[i];
        if (a==b) cout << 0 << endl;
        else if (Dist[a][b] < INF) cout << Dist[a][b] << endl;
        else cout << -1 << endl;
    }
}