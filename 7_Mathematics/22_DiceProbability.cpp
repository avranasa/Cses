#include<bits/stdc++.h>
using namespace std;
#define int long long 
  
signed main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int n, a, b;
    double P[101][601]={0}, S_tot=0, Sab=0;
    cin >> n >> a >> b;
    for (int i=0; i<6; i++) P[0][i] = 1.0/6.0;//first round
    for (int r=0; r<n-1; r++)//previous round
        for(int i=r; i<6*(r+1); i++)//in previous round min sum is r and max 6*r
            for(int j=1; j<=6; j++)
                P[r+1][i+j] += P[r][i]/6.0;    
    for(int i=a-1; i<b; i++)  Sab += P[n-1][i];
    cout<<setprecision(6)<<fixed;
    cout<< Sab;
}