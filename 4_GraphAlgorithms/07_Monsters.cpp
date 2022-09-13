//A very interesting way to complicate the problem is to force all the Monster to make a move per
//time step and not be able to remain in their position.... (solution... if a monster goes to one
//cell at move I then it can only be back at that cell at move I+2*k with k a positive integer)

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <tuple>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;


int main(){
    int n, m, Ax, Ay, Ax_init, Ay_init, Mx, My, x_new, y_new, N_moves, incr_x, incr_y;
    char C, Dir;
    cin >> n >> m;
    queue < pair<int,int>> M;
    queue < tuple<int, int, int>> A;
    string path;
    int  Map[n+2][m+2]; 
    bool Visited[n+2][m+2];
    char From[n+2][m+2];
    //The Map will be a matrix of size (n+2,m+2). Each cell takes a non-negative value. If 
    //it takes k it means that you are allowed to get to that cell only in less than k moves.
    //So, if it is zero it means you cannot get to that cell.    
    for(int i=0;i<=n+1;i++)
        for(int j=0; j<=m+1;j++) {
            Map[i][j] = 0;
            Visited[i][j] = false;
        }

    
    for(int i=1;i<=n;i++){
        for(int j=1; j<=m;j++){
            cin >> C;
            if (C=='A') {
                A.push({i,j,0});
                Ax_init = i;
                Ay_init = j;
            }
            if (C=='M') M.push({i,j});
            if ((C=='.')||(C=='A')) Map[i][j]= n*m + 2;//more than the maximum allowed moves
        }
    }

    /*
    //      TOUGHER THAN WHAT YOU THINK ... 
    //The solution below is suboptimal!!! Taking one monster at a time 
    //and checking first all the  positions it can go and the go to the
    //next one and check again can lead to very slow performance in some
    //corner case. For example if you have O(n*m) monsters and each one
    //if it does independetly the search has to pass 0(n) cells you have
    //in total complexity 0(n*n*m)...
    //for example:
    // M.M.M.
    // M.M.M.
    // M.M.M.
    // M.M.M.
    // M.M.M.
    // M.M.M. and so on..

    //If, on the other hand, in evey iteration you check for k steps
    //to which new cells each monster can go, you get complexity 0(n*m)
    //which is the number of cells... the reason is that you compute 
    //SIMULTANIOUSLY for all monsters their voronoi and stop... 

    queue <tuple <int, int, int> > Q; //pos_x, pos_y, Num_moves
    while (!M.empty()){ 
        tie(Mx, My) = M.front();
        M.pop();
        Q.push({Mx,My,0});
        while (!Q.empty()){
            tie(Mx, My, N_moves) = Q.front();
            Q.pop();         
            //if (N_moves > Map[Mx][My]) continue;
            N_moves++;   
            if (N_moves < Map[Mx+1][My]){
                Map[Mx+1][My] = N_moves;
                Q.push({Mx+1, My, N_moves});
                }
            if (N_moves < Map[Mx-1][My]) {
                Map[Mx-1][My] = N_moves;
                Q.push({Mx-1, My, N_moves});
                }
            if (N_moves < Map[Mx][My+1]) {
                Map[Mx][My+1] = N_moves;
                Q.push({Mx, My+1, N_moves});
                }
            if (N_moves < Map[Mx][My-1]) {
                Map[Mx][My-1] = N_moves;
                Q.push({Mx, My-1, N_moves});
                }       
        }
    }
    */

    map <char, pair<int, int>> Moves={ {'D',{1,0}}, {'U',{-1,0}}, {'R',{0,1}}, {'L',{0,-1}}};
    
    while (!M.empty()){ 
        tie(Mx, My) = M.front();
        M.pop();
             
        //if (N_moves > Map[Mx][My]) continue;
        N_moves = Map[Mx][My] + 1;   
        for (auto const& move: Moves){
            tie(incr_x, incr_y) = move.second;
            if (N_moves < Map[Mx+incr_x][My+incr_y]){
                Map[Mx+incr_x][My+incr_y] = N_moves;
                M.push({Mx+incr_x,My+incr_y});
            }
        }
    }
    
    
    bool found_path = false;
    while (!A.empty()){
        tie(Ax, Ay, N_moves) = A.front();
        A.pop();
        Visited[Ax][Ay] = true;
        if ((Ax==1) || (Ax==n) || (Ay==m) || (Ay == 1)) {
            found_path = true;
            break;
        }
        N_moves ++;
        for (auto const& move: Moves){
            Dir = move.first;
            tie(incr_x, incr_y) = move.second;
            x_new = Ax+incr_x;
            y_new = Ay+incr_y;
            if (Visited[x_new][y_new]) continue;
            if (N_moves >= Map[x_new][y_new]) continue;
            A.push({x_new, y_new, N_moves});
            From[x_new][y_new] = Dir;
        }
    }
     

    if (found_path){
        n = 0;
        cout << "YES" << endl << N_moves << endl;
        while ((Ax!=Ax_init)||(Ay!=Ay_init)){
            Dir = From[Ax][Ay];
            path.push_back(Dir);
            Ax = Ax - Moves[Dir].first;
            Ay = Ay - Moves[Dir].second;
        }
        reverse(path.begin(),path.end());//library "algorithm"
        cout << path ;
    }
    else cout << "NO" ;
    
}

