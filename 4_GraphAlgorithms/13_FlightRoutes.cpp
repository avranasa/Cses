#include <bits/stdc++.h>
#define ll long long
#define INF 2e18
using namespace std;

int main(){
    int n,m,k, a,b;
    cin >> n >> m >> k;
    ll c,dist;
    vector <pair <int,ll>> Adj[n];
    int Visited[n]={0};//how many times each city is visited
    for (int i=0;i<m; i++){
        cin >> a >> b >> c;
        Adj[a-1].push_back({b-1,c});
    }
    priority_queue <pair <ll, int>> Q;
    Q.push({0,0});
    Visited[0]++;
    while (Visited[n-1]<k){
        tie(dist,a) = Q.top(); Q.pop();//dist<0 because the priority queue is ordering in increasing order...
        if (Visited[a]>k) continue;
        if (a==n-1) {
            cout << -dist <<" ";
            //continue; //We do not consider a route that goes to the last city and then returns to it
        }
        Visited[a] ++ ;
        for(auto p: Adj[a]){
            tie(b,c) = p;
            if (Visited[b]>k) continue;
            Q.push({dist-c,b});
        }
    }
}