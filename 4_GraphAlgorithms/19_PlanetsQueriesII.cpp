/*
Preprocessing:
To every node you assign two or three numbers: the first number correspond to the path with which it is reached that node.
Then if the node does not belong in a cycle there is one more number assigned which is the relative distance (counted as 
number of steps) for the root of the path. If the node belongs to cycle then second number is again the relative distance
from the root of the path but after doing once the cycle.
Each time you start from a random node that is not yet visited and you make it the root of a new path and you rank it first.
With DPF you visit new unvisited nodes you assign them to the id of the path to those nodes and also the distance covered. In 
case you visit a previously visited node X there are two cases: 1) the node X is the root of a previous path then you go back 
and change the id of path of the nodes you visited with the id of the path of the node X. Also you correct their rankings in
the path. Denote the node X as not a root. 2) the node X is not the root of any path. Then return and only correct the numbering.


TRICKY TEST
The 13-th test is very tricky!!! The graph is given in a way that the paths you discover are:
path-1: 1->n->n
path-2: 2->(n-1)->n
path-3: 3->(n-2)->(n-1)
path-4: 4->(n-3)->(n-2)
...
The problem is that if you start from node n/2+1 then you will have to check all the n/2 paths...linear
complexity when you need logarithmic... !!!


Method not implemented:
After havng done the Fill_p and for each node a you have computed the P[a] you can check the distance from a 
to b as  dist=P[b-1][1]-P[a-1][1] (or P[b-1][2]-P[a-1][1] to account for cycle) anc check if with dist number of
steps starting from a you arrive to b. To find in a logarithmic way if indeed you land on b you can use the 
PlanetQueriesI.cpp code that implements the idea of 7.5.1. of the book.

*/

#include <bits/stdc++.h>
using namespace std;
#define INF 1e8

void Fill_P (int adj[], int P[][3], bool Root[], bool Visited[], int node, int path_id, int dist, vector <int> & v_out){
    // In principle the output is the vector v_out. If the size is 4 then its elements correspond to
    // (this_node_path_id, this_node_dist_from_node's_path_root, the_path_that_this_path_connects_to, the_common_node_of_those_paths )
    // and if size is 2 it corresponds to only the first two.
    if (!Visited[node]){
        Visited[node] = true;
        P[node][0] = path_id;//might be changed in the return...
        P[node][1] = dist;
        Fill_P(adj, P, Root, Visited, adj[node], path_id, dist+1, v_out);
        P[node][0] = v_out[0]; P[node][1] = v_out[1]; 
    }
    else{
        if (path_id == P[node][0]){
            //Path has a cycle
            if (P[node][2]==INF) {
                //A second time on the cycle 
                P[node][2] = dist;
                Fill_P(adj, P, Root, Visited, adj[node], path_id, dist+1, v_out);
            }
            else  v_out.insert(v_out.end(),{path_id, dist} );
        }
        else if (Root[node]){
            // a previously found path found that has as root this node
            Root[node] = false; 
            v_out.insert(v_out.end(),{P[node][0], P[node][1]});//while returning change the path id of the nodes
        }
        else{
            // a previously found path found that does not have as root this node
            v_out.insert(v_out.end(),{path_id, P[node][1], P[node][0], node});
        }
    }
    v_out[1] --;
}


int main(){    
    ios::sync_with_stdio(0);
    cin.tie(0);  cout.tie(0);
    int Method = 2;
    /*
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    */

    //Input
    int n, q, a, b, path_id=0, x, other_root, other_path, this_root, common_node;
    cin >> n >> q;
    int adj[n], P[n][3];//P[i][0] the path the i-th node belongs. P[i][1] distance from root of i-th node without using any cycle
                        //P[i][2] distance from root of i-th node using a cycle (INF means no cycle can be used)
    for (int i=0; i<n; i++) {
        cin >> b;
        adj[i] = b-1;
        P[i][1] = INF; P[i][2] = INF;
    }
    
    //Preprocessing... filling matrix P
    bool Visited[n] = {false}, Root[n]={false};
    vector <array<int, 3>> Paths;//the i-th element is (j,n,r) which means the i-th path with root r connects to the j-th path at node n   
    vector <int> v_out;    
    if (Method == 0){    
        //THIS METHOD CAN ALSO BE VERY SLOW (test-9 and test-10)
        for (int i=0;i<n;i++){
            if (Visited[i]) continue;
            v_out.clear();
            Root[i] = true;
            Fill_P(adj, P, Root, Visited, i, path_id, 0, v_out);
            if (v_out[0] != path_id) continue; // a previous path was extended
            if (v_out.size() == 4) {//path connects to a previous found one
                this_root = i;
                other_path = v_out[2];
                common_node =  v_out[3];
                other_root = Paths[other_path][2]; //the root of the path that this path is connected to            
                if (P[other_root][1] <= P[this_root][1]) Paths.push_back({other_path, common_node, this_root});
                else{
                    //Swap the beggining parts of the path. The goal is to favor the emergence of one big path with multiple 
                    //small ones connected to it rather than many small paths connected to each other
                    Paths[other_path][2] = this_root;//changing the root
                    Paths.push_back({other_path, common_node, other_root});
                    x = other_root;
                    while(x != common_node){
                        P[x][0] = path_id; 
                        x = adj[x];
                    }
                    x = this_root;
                    while(x != common_node){
                        P[x][0] = other_path; 
                        x = adj[x];
                    }                    
                }
            }
            else Paths.push_back({ path_id,-1,i});//new independent path was found
            path_id ++;
        }
    }
    else if (Method==1){        
        // PASSES the TRICKY TEST in a meta-sneaky way! Does not allow the edges to be given in a sneaky sequence....
        vector <int> nodes;
        for (int i=0; i<n; i++) nodes.push_back(i);
        random_shuffle(nodes.begin(), nodes.end()); 
        for (auto i : nodes){
            if (Visited[i]) continue;
            v_out.clear();
            Root[i] = true;
            Fill_P(adj, P, Root, Visited, i, path_id, 0, v_out);
            if (v_out[0] != path_id) continue; // a previous path was extended
            if (v_out.size() == 4) Paths.push_back({v_out[2], v_out[3],i});//path connects to a previous found one
            else Paths.push_back({ path_id,-1,i});//new independent path was found
            path_id ++;
        }
    }
    else if (Method==2){
        // It runs twice the Fill_P function and the first time you do it only to discover the roots to the 
        // biggest paths. This is only in order the second time to begin from those nodes first so as to create
        // the largets paths possible
        priority_queue <pair<int,int>> nodes;
        for (int i=0; i<n; i++){
            if (Visited[i]) continue;
            v_out.clear();
            Root[i] = true;
            Fill_P(adj, P, Root, Visited, i, path_id, 0, v_out);
            nodes.push({-P[i][1],i} ) ;//a new path with a new root is discovered
            path_id ++;
        }
        for (int i=0; i<n; i++){
            Visited[i]=false; Root[i]=false; P[i][1]=INF; P[i][2]=INF;
        }
        path_id = 0;
        while(!nodes.empty()){
            a = nodes.top().second; nodes.pop();
            if (Visited[a]) continue;
            v_out.clear();
            Root[a] = true;
            Fill_P(adj, P, Root, Visited, a, path_id, 0, v_out);
            if (v_out[0] != path_id) continue; // a previous path was extended
            if (v_out.size() == 4) Paths.push_back({v_out[2], v_out[3],a});//path connects to a previous found one
            else Paths.push_back({ path_id,-1,a});//new independent path was found
            path_id ++;
        }
       
    }
        
   
    //Output
    for (int i=0; i<q; i++){
        cin >> a >> b;

        x = a-1;
        path_id =  P[b-1][0];
        while (P[x][0] != path_id) {
            x = Paths[P[x][0]][1];
            if (x == -1) break;
        }
        if (x==-1)  cout << -1 << '\n';
        else if (P[x][1]<=P[b-1][1]) cout << P[b-1][1] - P[a-1][1] << '\n'; //no need to cycle :-)
        else if (P[b-1][2]<INF) cout << P[b-1][2] - P[a-1][1] <<  '\n'; //node b belongs in a cycle which we use
        else cout << -1 << '\n';
    }  
    
  
}