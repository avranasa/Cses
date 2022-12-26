#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define int long long
#define _space_ <<' '<<
using namespace std;
const long long inf = 1LL<<60; //1.5e18, max(long long)= 9e18 = 2^63
const int md = 1000000007;

signed main(){
    int a, b, c, n, m, count=0, c_tot=0;
    cin >>n >> m;
    vector <pair<int,int>> Adj[n];
    bool Visited[n] = {false};
    //int Cost2City[n] ; fill(Cost2City, Cost2City+n, inf); //This step bearly decreases the time
    priority_queue <pair <int, int> > Q;//{Cost, node}
    for (int i=0; i<m; i++){
        cin >> a >> b >> c;
        Adj[a-1].push_back({b-1,c});
        Adj[b-1].push_back({a-1,c});
    }
    Q.push({0,0});
    while(!Q.empty()){
        tie(c,a) = Q.top(); Q.pop();
        if (Visited[a]) continue;
        Visited[a] = true;    
        //Cost2City[a] = -c;  
        c_tot -= c;  
        count += 1;
        for(auto p: Adj[a]){
            tie(b,c) = p;
            if (Visited[b]) continue;
            //if (Cost2City[b]<=c) continue;
            //Cost2City[b] = c;
            Q.push({-c,b});
        }
    }
    if (count == n) cout << c_tot;
    else cout << "IMPOSSIBLE";    
}