/*For the simpler version where you do not have to change the values then 
you can use the matrix where each cell [i,j] has two values. The [i,j] refers 
to the path from node i to the 2^j parent. The first value is the node that 
is the 2^j parent of node i and the second the maximum value along this path...*/
/*For this problem you would need a segment tree even for the simplest case 
where the tree is a line graph.*/


/*Heavy light decomposition is needed. For each heavy path a segment tree is created.*/

#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '  
#define _space_ <<' '<<
using namespace std;

int max_range_H(int a, int b, vector<int> & tree){
    int n = tree.size()/2, v=0;//the values are all bigger than 1.
    a+=n; b+=n;
    while (a<=b) {
        if (a%2==1) v=max(v,tree[a++]);
        if (b%2==0) v=max(v,tree[b--]);
        a/=2; b/=2;
    }
    return v;    
}

void upd_range_H(int k, int x, vector<int> & tree){
    int n = tree.size()/2;
    k += n;
    tree[k] = x;
    for (k/=2; k>=1; k/=2) 
        tree[k] = max(tree[2*k], tree[2*k+1]);
}

int min_depth_node(int a, int b, int n, int tree[][2]){
    //returns node with minimum depth in the given range
    a+=n; b+=n;
    int node_min, d_min = 2e9;//around the maximum of an integer (greater than n is fine also for this problem)
    while (a<=b) {
        if (a%2==1) {
            if (d_min > tree[a][1]){
                d_min = tree[a][1];
                node_min = tree[a][0];
            }
            a++;
        }
        if (b%2==0) {
            if (d_min > tree[b][1]){
                d_min = tree[b][1];
                node_min = tree[b][0];
            }
            b--;
        } 
        a/=2; b/=2;
    }
    return node_min;    
}

void upd_depth_range(int k, int depth, int node, int n, int tree[][2]){
    int k_min;
    k += n;
    tree[k][0] = node;
    tree[k][1] = depth;
    for (k/=2; k>=1; k/=2) {
        k_min = (tree[2*k][1]<tree[2*k+1][1]) ? 2*k : 2*k+1;
        tree[k][0]=tree[k_min][0];
        tree[k][1]=tree[k_min][1];        
    }
}

int DFS(int x, int Par[], vector<int> Adj[], int TreeDepth[][2], int & idx, int Idx[], int depth, int n, int & nH, int PosH[][2], vector<int> & SizeH){
    //Computes the TreeDepth structure used for finding the common ancestor
    //Computes the heavy paths likewise: 
    // -if a node is a leaf it enters in a new heavy path
    // -if a node has children then it enters to the heavy path of the child with the biggest sub-tree
    //Returns the size of the tree
    upd_depth_range(idx, depth, x, 2*n-1, TreeDepth);
    Idx[x] = idx ; 
    if ( Adj[x].size()==1 && x!=0) {//found a leaf. Create new heavy path.
        SizeH.push_back(1);
        PosH[x][0] = nH;
        PosH[x][1] = 0;//first element of each heavy path is a leaf
        nH++; 
        return 1; 
    }
    int s=1, s_ch, s_ch_max=-1, x_next_max;//size of subtree with (sub)root x
    for (int x_next: Adj[x]){
        if (x_next == Par[x]) continue;  
        Par[x_next] = x;    
        idx ++;
        s_ch = DFS(x_next, Par, Adj, TreeDepth, idx, Idx, depth+1, n, nH, PosH, SizeH);
        if (s_ch > s_ch_max){
            x_next_max = x_next;
            s_ch_max = s_ch;
        }
        s += s_ch;
        idx ++;
        upd_depth_range(idx, depth, x, 2*n-1, TreeDepth);        
    }
    //Put node x in the heavy path of x_next_max
    SizeH[PosH[x_next_max][0]]++;
    PosH[x][0] = PosH[x_next_max][0];
    PosH[x][1] = PosH[x_next_max][1]+1;//For each heavy path first goes the nodes that are deeper in the tree
    return s;
}


signed main(){
    //I do not check the case of the tree being just one node
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    int n, q, a, b, c, idx=0, nH=0, r, maxV;//nH is the number of heavy paths
    cin >> n >> q;
    int V[n], TreeDepth[2*(2*n-1)][2];//for every node we keep the id of node and distance from root while visiting 
                        //that node using DFS. Using min-segment tree
    int Ia, Ib, Idx[n], PosH[n][2], Par[n]; //Idx[i] shows the position of node i in the array TreeDepth
                //PosH[i][0] gives for node i its heavy path and PosH[i][1] its position inside this heavy path
    vector <int> Adj[n], SizeH; // SizeH[i] give the size of the i-th path
    for (int i=0; i<n; i++) cin >> V[i];
    for (int i=0; i<n-1; i++){
        cin >> a >> b; 
        a--; b--;
        Adj[a].push_back(b);
        Adj[b].push_back(a);
    }

    //Creating/Computing TreeDepth, nH, PosH, SizeH
    Par[0]=-1;
    DFS(0, Par, Adj, TreeDepth, idx, Idx, 0, n, nH, PosH, SizeH);

    //Creating segment trees for each heavy path.
    vector <int> TreeH[nH];
    int ParH[nH]; //will show for each heavy path the next node towards the root after the last node of the heavy path
    for(int i=0; i<nH; i++) TreeH[i].resize(2*SizeH[i], 0);
    for(int x=0; x<n; x++) {
        upd_range_H(PosH[x][1], V[x], TreeH[PosH[x][0]]);
        if (PosH[x][1]==SizeH[PosH[x][0]]-1) ParH[PosH[x][0]]=Par[x];
    }    
    
    //Answering the queries
    for(int i=0; i<q; i++){
        cin >> r >> a >> b; 
        a--;
        if (r==1) upd_range_H(PosH[a][1], b, TreeH[PosH[a][0]]); 
        else{
            b--;
            Ia = Idx[a]; Ib = Idx[b];
            if (Ia>Ib) swap(Ia, Ib);
            c = min_depth_node(Ia, Ib, 2*n-1, TreeDepth);//common lowest ancestor
            maxV = 0;
            for(int x: {a,b}){
                for(;;){
                    if (PosH[x][0]==PosH[c][0]) {//same heavy path
                        maxV=max(maxV, max_range_H(PosH[x][1], PosH[c][1], TreeH[PosH[x][0]]));
                        break;
                    }
                    else{//different heavy path
                        //SizeH[PosH[x][0]]-1 is the last element of the heavy path node x belongs
                        maxV=max(maxV, max_range_H(PosH[x][1], SizeH[PosH[x][0]]-1, TreeH[PosH[x][0]]));
                        x = ParH[PosH[x][0]];            
                    } 
                }
            } 
            cout << maxV _space;                                   
        }
    }
}
