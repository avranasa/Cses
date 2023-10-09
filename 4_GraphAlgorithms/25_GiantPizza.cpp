//WAY 1: For each Constrraint (A,B) (i.e. A>0 means include A ingredient and 
//A<0 exclude it) create two directed edges: (-A->B) and (-B->A): the first edge mean that 
// if you choose -A then you much choose B. The problem now becomes 
//choosing for each ingredient X either +X of -X, but also having to choose for every node
//all other nodes that you could get to them through any path... if you find that a certain
//ingredient if you have or you if do not have it you still cannot satisfy all families then
//there is no solution. (btw the graph is somehow  symmetrical since for each edge (A,B)
// there is also the edge (-A,-B) )

//WAY 2: Create a graph that for each ingredient there are two nodes one (+x) representing having 
//the ingredient and the other (-x) excluding it. Each edge is the condition that makes 
//impossible one family to be satisfied... for example if an input +1 +2 is given 
//then an edge -1,-2 will be put. Also you put an edge for (+x,-x) for every x-ingredient (as it
// you either put or not the x-ingredient). The goal is to choose a subset S of nodes with cardinality n
//(i.e. the maximum possible size) such that no two nodes are connected by an edge. The complement subset
//may have nodes connected by edges (i.e. the graph should not necessarily be bipartite to accept
//a solution). <= Not that easy to solve and the type of solutions I think end up very similar to WAY 1
 
//Other ways that solve the 2SAT problem would also work here!
 
#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
using namespace std;

void DFS(vector<int> Adj[], int x, bool visited[], vector<int> & L){
    if (visited[x]) return;
    visited[x] = true;
    for(int x_new: Adj[x]){        
        DFS(Adj, x_new, visited, L);
    }
    L.push_back(x);
} 

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);  cout.tie(0);
    int n, m, x, a, b, WAY = 2;
    bool feasible;
    char s;
    cin >> n >> m;
    int sol[m] = {0}; //if i-th position is 0 means not yet decided, if 1 means include i ingredient and -1 exclude it
    vector <int> Constr[2*m];//from [0,...,m-1] is for including an ingredient. The rest for excluding
    vector <int> Constr_inv[2*m]; // for WAY==2.. (kosaraju)
    for(int i=0; i<n; i++){
        cin >> s >> x;
        a = x-1;
        if (s=='-') a += m;
        cin >> s >> x;
        b = x-1;
        if (s=='-') b += m;
        Constr[(b+m)%(2*m)].push_back(a);//(-B->A)
        Constr[(a+m)%(2*m)].push_back(b);//(-A->B)
        Constr_inv[a].push_back((b+m)%(2*m));//for kosaraju
        Constr_inv[b].push_back((a+m)%(2*m));//for kosaraju
    }
    if (WAY==1){    
        /*This algorithm runs most of the times very fast. But there can be designed a adversarial example where
        it can go the complexity instead of  O(n*log(n)) to O(n^2). One of the examples in the cite (cses.fi) is like
        this. Luckily, in order to fall into O(n^2) complexity the sequence of the nodes we check should be a 
        very specific one and even slightly different input solves the problem. In the code the lines "1-5" randomize 
        the input sequence so the "adversarial" case becomes practically impossible. Without those lines and 
        instead using line 6 then the example of the cite that is adversarial is:
        100000 100000
        - 1 + 2
        - 2 + 3
        ...
        - k + (k+1)
        ...
        - 99999 + 100000
        - 99999 - 100000
        */
        int Range[m], i; //1
        iota(Range,Range+m,0);
        unsigned seed = chrono::system_clock::now().time_since_epoch().count(); //2
        shuffle(Range, Range+m, default_random_engine(seed)); //3  
        //for(int i=0; i<m; i++){ //6       
        for(int k=0; k<m; k++){ //4
            i = Range[k]; //5                   
            if (sol[i] != 0) continue;
            // check including or not the i-th ingredient        
            for (int j=0; j<2; j++){
                feasible = true;
                x = (j==0) ? i : i+m;//having or not having the i ingredient
                queue<int> q, sol_new_x;//sol_new_x used to revert the decision of choosing x
                q.push(x);  sol_new_x.push(x);
                sol[x%m] = (x<m) ? 1 : -1;
                while((!q.empty()) && feasible){
                    int s= q.front();  q.pop();
                    for (auto x_new : Constr[s]){
                        if (sol[x_new%m]==0) {
                            q.push(x_new);  sol_new_x.push(x_new);
                            sol[x_new%m] = (x_new<m) ? 1 : -1;                    
                        }
                        else if (((sol[x_new%m]>0)&&(x_new>=m)) ||
                                ((sol[x_new%m]<0)&&(x_new<m))){
                                    feasible = false;
                                    //reverting to previous state... now sol_new_x is being used                
                                    while(!sol_new_x.empty()){
                                        sol[sol_new_x.front()%m] = 0;
                                        sol_new_x.pop();
                                    }
                                    break;
                                }
                    }                
                }
                if (feasible) break;
            }
            if (!feasible){
                cout << "IMPOSSIBLE";
                return 0;
            }
        }
    }
    else if (WAY==2){
        //Kosaraju's algorithm 
        //1st DFS to create list L
        vector <int> L;
        bool visited[2*m] = {false};
        for(x=0; x<2*m; x++)
            DFS(Constr, x, visited, L);
        //for(auto p: L) cout << p << " ";
        
        //2nd DFS to identify the components. 
        vector<vector <int>> L_Comp;
        for(x=0; x<2*m; x++) visited[x] = false;
        for(x=2*m-1; x>=0; x--){//component L_Comp[i] cannot have a path leading to L_Comp[j] if i>j
            vector <int> aux;
            DFS(Constr_inv, L[x], visited, aux);            
            L_Comp.push_back(aux);
        }
        // Use the Components to solve 2-Sat
        int value, Comp_V[m]={0};//Comp_V[i] indicates which component set the value of variable i
        for(int C=L_Comp.size()-1; C>=0; C--){
            //cout << endl;
            for(auto var:L_Comp[C]){
                value = (var<m) ? 1 : -1;
                //cout << value * (var%m) << "  ";
                if (sol[var%m]==0) {
                    sol[var%m] = value;
                    Comp_V[var%m] = C+1;
                }
                else if ((sol[var%m]!=value) && (Comp_V[var%m] == C+1)) {
                    cout << "IMPOSSIBLE";
                    return 0;                    
                }
            }
        }    
    }
    
    for(int i=0; i<m; i++) 
        if (sol[i]==1) cout <<  "+ ";
        else if  (sol[i]==-1) cout <<  "- ";
}