//Solved it with one DFS and a Union-Find type of algorithm/structure... You can solve 
//it also using Kosaraju's Algorithm for finding connected components which uses 2 DFS...

#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
using namespace std;
#define INF 1e8

int FindCapital(int ToCapital[],int x){
    if (ToCapital[x]==x) return x;
    ToCapital[x] = FindCapital(ToCapital, ToCapital[x]);
    return ToCapital[x] ;
} 

void DFS(int s, vector<int> A[], int ToCapital[], int Path[]){
    int rank_of_cap = INF, new_ToCapital; //points to the oldest planet/node/capital
    for (int s_new: A[s]){
        if (ToCapital[s_new]==-1){
            Path[s_new] = Path[s] + 1;
            ToCapital[s_new] = s_new;//new node is a kingdom on its own with capital.
            DFS(s_new, A, ToCapital, Path);
        }
        new_ToCapital = FindCapital(ToCapital, s_new);
        //SCENARIO 2:
        if (Path[new_ToCapital]==-1) continue;//Imagine scenario 1->2->3->4->5->1 and then
                            //  you check 2->4. That time node 4 has Path=-1 and points to 1.

        //SCENARIO 1:
        if (Path[new_ToCapital]<rank_of_cap)   {
            //found an older-ranked capital
            rank_of_cap = Path[new_ToCapital];
            ToCapital[s] = new_ToCapital;
        } 
    }
    Path[s] = -1;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);  cout.tie(0);
    // Similar to 23_FlightRoutesCheck but the Way-1 solution is not easily applicable here.
    // Think for example a "linear" graph 1->2->3->...->n and how this Way-1 would work. 
    int n, m, a, b;
    cin >> n >> m;
    vector <int> A[n];
    for (int i=0; i<m; i++){
        cin >> a >> b;
        A[a-1].push_back(b-1);
    }
    // Reasoning of DFS solution.
    // Every new node you put it in a new kingdom/set (i.e. capital is itself). If from a node A you visit
    //  a node  B that is already in an older kingdom that has capital C then there are two scenarios. 
    // SCENARIO 1: There is a Path from C to A, so you move also node A to the same kingdom (by setting ToCapital[A]=C), 
    // SCENARIO 2: otherwise, (i.e. when Path[new_ToCapital]==-1) you continue your search.
    int kingdom[n], ToCapital[n], Path[n], max_k = 0, capital;//Based on Union-Find structure. ToCapital is 
        // moving you to a node/planet that is or is closer to the capital of the kingdom. A capital of a 
        // kingdom point to itself (i.e. if x is capital then ToCapital[x]=x). If a node has Path[x]=-1 then
        // it is either already processed and fixed (i.e. known the ToCapital[x]) or not yet visited by DFS.

    for(int i=0; i<n; i++){ToCapital[i]=-1; Path[i] = -1; kingdom[i]=0;} 
    for(int i=0; i<n; i++){
        if (ToCapital[i]>=0) continue;//already visited and placed to a formed kingdom with a capital
        Path[i] = 0;
        ToCapital[i] = i ;
        DFS(i, A, ToCapital, Path);
    }
    for (int i=0; i<n; i++){
        capital = FindCapital(ToCapital, i);
        if (kingdom[capital]==0){
            max_k ++;
            kingdom[capital] = max_k;
        }
        kingdom[i] = kingdom[capital];
    }
    cout << max_k _endl;
    for (int i=0; i<n; i++) cout << kingdom[i] _space;
}