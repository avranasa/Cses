#include <bits/stdc++.h>
#define INF 2e18
#define ll long long 
using namespace std;


/*BE CAREFUL...  We want to check not just if a positive cycle 
exists but a cycle that is included by a path from 1 to n... It is wrong to only check if
the distance from node 1 to n has been increase within [n, 2*(n-1)] steps... For example:

4 5
1 2 1
2 3 1
3 2 1
2 4 1
1 4 1000000000

// You want to take the decision (and be termed as visited) for some node when you are certain that either there is or not
// a path to the targeted node. To know that you have first to check all the children and make sure that they themselves have 
// or not a path to the target. But if there is a cycle between parent and a child then each one will wait for the other 
// to become first take the decision to afterwards decide if there is a path to the target node... an infinite loop...
// ... so a you actually need the parent first to take a decision and then the children to decide according to the father
//(again think of the above example...)
// This means you need to change the direction of each edge and start from the city "n" which you trivially take the decision
// and continue to check which nodes you  can reach from n with inverted edges
*/
void Reach_n(vector<int> Adj_inv[],int node, bool Path_to_n[]){
    Path_to_n[node] = true;
    for (auto new_node: Adj_inv[node])
        if (!Path_to_n[new_node]) Reach_n( Adj_inv, new_node, Path_to_n);
}



int main(){
    //Necessary variables and initializations
    int n, m, a, b;
    cin >> n >> m;
    ll Dist[n], d, new_d;
    for(int j=0;j<n;j++) Dist[j] = -INF;
    vector< pair<int,ll>> Adj[n];
    vector<int> Adj_inv[n];
    queue <int> Q;
    bool InQueue[n] = {false}, Positive_cycle_1_to_n=false, Path_to_n[n]={false}, Visited[n] = {false};
    int Steps[n]={0}, max_steps=0;
    for(int j=0; j<m; j++){
        cin >> a >> b >> d;
        Adj[a-1].push_back({b-1,d});
        Adj_inv[b-1].push_back(a-1);
    }

    //finding all nodes that reach node n
    Reach_n(Adj_inv, n-1, Path_to_n);

    //finding maximum distance to  n
    Q.push(0);
    InQueue[0] = true;
    Dist[0] = 0;
    Steps[0] = 0;
    while (!Q.empty()){
        if ((Positive_cycle_1_to_n) || (max_steps==n+1)) break;
        a = Q.front(); Q.pop();
        InQueue[a] = false;
        for(auto p : Adj[a]){
            tie(b,d) = p;
            new_d = Dist[a] + d;
            if (new_d>Dist[b]){
                Dist[b] = new_d;
                Steps[b] = Steps[a] + 1;
                max_steps = max(max_steps,Steps[b]);
                if (!InQueue[b]){
                    Q.push(b);
                    InQueue[b]=true;
                }
                if ((Steps[b] == n) && (Path_to_n[b])) Positive_cycle_1_to_n = true;
            }
        }        
    }
    cout << (Positive_cycle_1_to_n ? -1 : Dist[n-1] );
    
}