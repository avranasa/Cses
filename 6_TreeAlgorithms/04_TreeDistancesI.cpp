#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
using namespace std;
const long long inf = 1LL<<60; //1.5e18, max(long long)= 9e18 = 2^63
const int md = 1000000007;

void check_through_children(vector<int> adj[], int node, int prev_node, vector<pair<int,int>> & max_length_1, vector<pair<int,int>> & max_length_2){
    int len1=0, len2=0, len, node1=-1, node2=-1;//always will try len1 to be bigger than len2
    for (int next_node: adj[node]){
        if (next_node==prev_node) continue;
        check_through_children(adj, next_node, node, max_length_1, max_length_2);
        len = max(max_length_1[next_node].first+1, max_length_2[next_node].first+1);
        if (len==0){//first child inspected
            len1=len;
            node1=next_node;
        }
        else if (len1<len){
            len2=len1;  node2=node1;
            len1=len; node1=next_node;
        }
        else if (len2<len){
            len2 = len;
            node2 = next_node;
        }
    }
    max_length_1[node] = {len1, node1};
    max_length_2[node] = {len2, node2};
}

void check_through_parent(vector<int> adj[], int node, int prev_node, vector<pair<int,int>> & max_length_1, vector<pair<int,int>> & max_length_2){
    int len1, len2, node1, node2;
    tie(len1, node1) = max_length_1[node];
    tie(len2, node2) = max_length_2[node];
    if (len1<len2){ 
        swap(len1,len2); swap(node1, node2);
    }
    for(int next_node: adj[node]){
        if (next_node==prev_node) continue;
        if ((node1 != next_node) && (len1+1 > max_length_2[next_node].first))
            max_length_2[next_node] = {len1+1,node};
        if ((node1 == next_node) && (len2+1 > max_length_2[next_node].first))
            max_length_2[next_node] = {len2+1,node};        
        check_through_parent(adj, next_node, node, max_length_1, max_length_2);
    }
}

signed main(){
    int n, a, b;
    cin >> n;
    vector <int> adj[n];
    vector <pair<int,int>> max_length_1(n,{0,-1}), max_length_2(n,{0,-1});//max_length_1, and _2 provide for every node the two 
        // maximum distances to any other possible node (if there exists).  max_length_1, and _2 correspond to two paths that 
        // must have different first node. The saved pair is {max_dist, first_node_of_path}
    for(int i=0; i<n-1; i++){
        cin >> a >> b;
        adj[a-1].push_back(b-1);
        adj[b-1].push_back(a-1);
    }
    check_through_children(adj, 0, 0, max_length_1, max_length_2);
    check_through_parent(adj, 0, 0, max_length_1, max_length_2);
    for (int i=0; i<n; i++) cout<< max(max_length_1[i].first,max_length_2[i].first)   _space;   
}