//WAY 1: For each constraint (A,B) (i.e. A>0 means include A ingredient and 
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
 
 
int main(){
    int n, m, x, a, b;
    bool feasible;
    char s;
    cin >> n >> m;
    vector <int> Const[2*m];//from [0,...,m-1] is for including an ingredient. The rest for excluding
    for(int i=0; i<n; i++){
        cin >> s >> x;
        a = x-1;
        if (s=='-') a += m;
        cin >> s >> x;
        b = x-1;
        if (s=='-') b += m;
        Const[(b+m)%(2*m)].push_back(a);//(-B->A)
        Const[(a+m)%(2*m)].push_back(b);//(-A->B)
        //cout << (b+m)%(2*m) + 1 _space_ a+1 << " :  "<<(a+m)%(2*m)+1 _space_ b+1 <<endl;
    }
    int sol[m] = {0}; //if i-th position is 0 means not yet decided, if 1 means include i ingredient and -1 exclude it
    for(int i=0; i<m; i++){
        if (sol[i] != 0) continue;
        // check including the i-th ingredient        
        for (int j=0; j<2; j++){
            feasible = true;
            x = (j==0) ? i : i+m;//having or not having the i ingredient
            queue<int> q, sol_new_x;//sol_new_x used to revert the decision of choosing x
            q.push(x);
            sol_new_x.push(x);
            sol[x%m] = (x<m) ? 1 : -1;
            while((!q.empty()) && feasible){
                int s= q.front();  q.pop();
                for (auto x_new : Const[s]){
                    if (sol[x_new%m]==0) {
                        q.push(x_new);    
                        sol_new_x.push(x_new);
                        sol[x_new%m] = (x_new<m) ? 1 : -1;                    
                    }
                    else if (((sol[x_new%m]>0)&&(x_new>=m)) ||
                             ((sol[x_new%m]<0)&&(x_new<m))){
                                feasible = false;
                                //reverting to previous state'
                            
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
    for(int i=0; i<m; i++) 
        if (sol[i]==1) cout <<  "+";
        else if  (sol[i]==-1) cout <<  "-";
}