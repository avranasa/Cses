#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define INF 2e18

int main(){
    int n,m,a,b, max_steps, root, node_ArrivedFrom_NegCycle = -1, node_in_NegCycle;
    cin >> n >> m;
    int From[n], Steps[n]={0};
    ll Dist[n], c, new_dist;
    bool Visited[n]={false},visited_all=false, InCycle=false;
    vector <pair< int, ll >> Adj[n];
    vector <int> Path;
    queue <int> Q;
    for (int i=0; i<n; i++) Dist[i] = INF;
    for (int i=0; i<n; i++) From[i] = -1;
    for (int i=0; i<m; i++){
        cin >> a >> b >> c;
        Adj[a-1].push_back({b-1,c});
    }

    
    root = 0;
    while((!visited_all) && (node_ArrivedFrom_NegCycle == -1)){
        Q.push(root);
        Dist[root] = 0;
        max_steps = 0;
        while ((!Q.empty()) && (node_ArrivedFrom_NegCycle == -1)){
            a = Q.front(); Q.pop();
            Visited[a] = true;
            for(auto p: Adj[a]){
                tie(b,c) = p;
                new_dist = Dist[a] + c;
                if (new_dist < Dist[b]){
                    Steps[b] = Steps[a]+1;
                    max_steps = max(max_steps, Steps[b]);
                    Dist[b] = new_dist;
                    From[b] = a;
                    Q.push(b);
                    if (max_steps == n) node_ArrivedFrom_NegCycle = b;
                }
            }
        }
        visited_all = true;
        for(int i=0;i<n;i++){
            if (!Visited[i]){
                root = i;
                visited_all = false;
                break;
            }
        }        
    }

    if (node_ArrivedFrom_NegCycle == -1) cout << "NO";
    else{
        a = node_ArrivedFrom_NegCycle;
        Path.push_back(a);
        while(!InCycle){
            a = From[a];
            Path.push_back(a);
            for(int i=0; i<Path.size(); i++) {
                if (Path[i]==From[a]){
                    InCycle=true;
                    break;
                }
            }
        }
        node_in_NegCycle = From[a];
        cout << "YES"<< endl << node_in_NegCycle+1<<" "; 
        for(auto r_it=Path.rbegin();r_it!=Path.rend();r_it++){
            cout << *r_it+1<< " ";
            if (*r_it==node_in_NegCycle) break;
        }       
        
    }
}