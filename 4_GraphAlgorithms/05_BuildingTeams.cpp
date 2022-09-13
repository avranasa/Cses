#include <bits/stdc++.h>
using namespace std;
 

int main(){
    int n, m, a, b, nod, team;
    cin >> n >> m;
    vector <int> Friends[n], Teams(n,0);
    for (int i=0; i<m; i++){
        cin >> a >> b;
        a--;b--;
        Friends[a].push_back(b);
        Friends[b].push_back(a);
    }
    
    queue <int> Q;
    for (int st_nod=0; st_nod<n; st_nod++){
        if (Teams[st_nod]!=0) continue;
        Q.push(st_nod);
        Teams[st_nod] = 1;
        while(!Q.empty()){
            nod = Q.front();
            Q.pop();
            team = 3-Teams[nod];
            for(auto next_nod:Friends[nod]){
                if (Teams[next_nod]==Teams[nod]){
                    cout<< "IMPOSSIBLE";
                    return 0;
                }
                else if (Teams[next_nod]==0){
                    Teams[next_nod]=team;
                    Q.push(next_nod);
                }
            }
        }
    } 
    for(int i=0;i<n;i++) cout <<Teams[i] << " ";

}