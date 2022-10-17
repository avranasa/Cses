#include <bits/stdc++.h>
using namespace std;

void topological_sort_dfs(vector <int> adj[], int node, int & curr_rank, vector <int> & Ranks){
    //we know that there is no cycle
    //if Ranks[i]<0 it means that the i-th node is not yet sorted.
    
    //cout << "  -> " <<node+1 <<" r "<<  curr_rank<< endl;
    for (int next_node : adj[node]){
        if (Ranks[next_node]>=0) continue;
        topological_sort_dfs(adj, next_node, curr_rank, Ranks);
    }
    
    Ranks[node] = curr_rank; curr_rank++;
}


int main(){
    /* You need to make a topological sort and to push the new nodes with that sorted rank in the priority queue. 
    This assures that the first nodes/cities to be examined are the ones that may be one of the first
    in the final path. This prohibits finding a node that can be placed in the beginning of a path and then
    having to update all the nodes statistics of the path. For example in the graph with edges:
    (1,2),(1,3),(3,2)(2,4),(4,5),(5,6) you might investigate first the nodes 1,2,4,5,6 and find that path
    and then you check the node 3 and you have to update all the rest of the path, i.e. 4,5,6.
    */
    int n, m, a, b, rank=0;
    cin >> n >> m;
    vector <int> adj[n], dist(n,0), prev_node(n,-1), Ranks(n,-1);//keeping the max distance
    vector <bool> in_queue(n,false);
    priority_queue <pair<int,int>> Q;
    //input
    for (int i=0; i<m; i++){
        cin >> a >> b;
        adj[a-1].push_back(b-1);
    }


    //Topological sorting
    topological_sort_dfs(adj, 0, rank, Ranks); //if some cities can not be reached by city 0 we do not have to sort them

    //find the path
    Q.push({Ranks[0],0});//starting from node 0 
    in_queue[0]=true;
    while (!Q.empty()) {
        a = Q.top().second; Q.pop();
        for (auto v: adj[a]){
            if (dist[v]>dist[a]) continue;
            dist[v] = dist[a] + 1;
            Q.push({Ranks[v],v});
            in_queue[v] = true;
            prev_node[v] = a;
        }
    }
    
    //print journey
    if (dist[n-1]==0){
        cout << "IMPOSSIBLE";
        return 0;
    }
    stack <int> journey;
    b = n-1;
    while (b!=0){
        journey.push(b);
        b=prev_node[b];
    }
    journey.push(0); 
    cout << journey.size() << endl;
    while (!journey.empty())  {
        cout << journey.top()+1<< " ";
        journey.pop();
    } 
    
}