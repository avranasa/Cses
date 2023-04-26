#include <iostream>
#include <vector>
#include <string>
using namespace std;
 
#define N 7//number of squares per edge
 
 
bool FeasibleNewMove(bool Occupied[N+2][N+2], short last_i, short last_j){
    if ((!Occupied[last_i-1][last_j] && !Occupied[last_i+1][last_j]) && (Occupied[last_i][last_j-1] && Occupied[last_i][last_j+1])) return false;//creating a close loop...
    if ((!Occupied[last_i][last_j-1] && !Occupied[last_i][last_j+1]) && (Occupied[last_i-1][last_j] && Occupied[last_i+1][last_j])) return false;//creating a close loop...
    return true;
}
 
 
bool CheckFinalCell(short last_i, short last_j, int N_steps){
    if ((last_i!=N) || (last_j!=1)) return true;
    if (N_steps == N*N-1) return true;
    else return false;
}
 
 
bool CheckOneWay(bool Occupied[N+2][N+2], short i, short j){
    if ( !Occupied[i-1][j] ){
        if (Occupied[i+1][j] && Occupied[i][j-1] && Occupied[i][j+1]) return true;
        else return false;
    }
    if ( !Occupied[i+1][j] ){
        if ( Occupied[i][j-1] && Occupied[i][j+1]) return true;
        else return false;
    }
    if ( !Occupied[i][j-1] ){
        if (Occupied[i][j+1]) return true;
        else return false;
    }
    if (!Occupied[i][j+1]) return true;
    return false;   
}
 
 
//void FillPaths(int &N_paths, vector<char> & current_path, bool Occupied[N+2][N+2], short last_i, short last_j){
void FillPaths(int &N_paths, bool Occupied[N+2][N+2], short last_i, short last_j, short &N_steps, char * RequestedPath){
    if ((last_i==N) && (last_j==1)){
        N_paths ++;
        return;
    } 
 
    /*//It made it slower the below "improvement"!
    vector <char> Moves= {'U','D','L','R'};
    for (char m:Moves){
        int new_last_i=last_i, new_last_j=last_j;
        if (m=='U') new_last_i--;
        if (m=='D') new_last_i++;
        if (m=='L') new_last_j--;
        if (m=='R') new_last_j++;
        if (!Occupied[new_last_i][new_last_j]){
            if (CheckOneWay(Occupied,new_last_i,new_last_j) ){
                char Moves[]= {m};
                break;
            }
        }
    }*/ 
    if (RequestedPath[N_steps]=='?'){
        for (char m:{'U','D','L','R'}){
            short new_last_i=last_i, new_last_j=last_j;
            if (m=='U') new_last_i--;
            else if (m=='D') new_last_i++;
            else if (m=='L') new_last_j--;
            else if (m=='R') new_last_j++;
            //if ((!Occupied[new_last_i][new_last_j]) && FeasibleNewMove(Occupied, new_last_i, new_last_j) && CheckFinalCell(new_last_i, new_last_j, current_path.size()+1)){
            if ((!Occupied[new_last_i][new_last_j]) && FeasibleNewMove(Occupied, new_last_i, new_last_j) && CheckFinalCell(new_last_i, new_last_j, N_steps+1)){
                Occupied[new_last_i][new_last_j] = true; 
                //current_path.push_back(m);
                //FillPaths(N_paths, current_path, Occupied, new_last_i, new_last_j);  
                FillPaths(N_paths, Occupied, new_last_i, new_last_j, ++N_steps, RequestedPath);  
                Occupied[new_last_i][new_last_j] = false; 
                //current_path.pop_back();
                N_steps--;
            }
        }
    }
    else{
        char m = RequestedPath[N_steps];
        short new_last_i=last_i, new_last_j=last_j;
        if (m=='U') new_last_i--;
        else if (m=='D') new_last_i++;
        else if (m=='L') new_last_j--;
        else if (m=='R') new_last_j++;
        //if ((!Occupied[new_last_i][new_last_j]) && FeasibleNewMove(Occupied, new_last_i, new_last_j) && CheckFinalCell(new_last_i, new_last_j, current_path.size()+1)){
        if ((!Occupied[new_last_i][new_last_j]) && FeasibleNewMove(Occupied, new_last_i, new_last_j) && CheckFinalCell(new_last_i, new_last_j, N_steps+1)){
            Occupied[new_last_i][new_last_j] = true; 
            //current_path.push_back(m);
            //FillPaths(N_paths, current_path, Occupied, new_last_i, new_last_j);  
            FillPaths(N_paths, Occupied, new_last_i, new_last_j, ++N_steps, RequestedPath);  
            Occupied[new_last_i][new_last_j] = false; 
            //current_path.pop_back();
            N_steps--;
        }
    } 
}
 
 
 
int main(){    
    ios::sync_with_stdio(0);
    cin.tie(0);  cout.tie(0);
    //begin from point (1,1) and final position (N,1)
    //vector <char> current_path;//**************SOS*************** YOU DO NOT HAVE TO COMPUTE THE PATH! IT DOUBLES THE TIME IF YOU DO
    int N_paths=0;
    short N_steps = 0;
    bool Occupied[N+2][N+2];//a wall surrounding the grid ... i.e. (1+N+1)x(1+N+1)
    for(int i=0;i<N+2; ++i){//the wall
        Occupied[i][0]=true;
        Occupied[i][N+1]=true;
        Occupied[0][i]=true;
        Occupied[N+1][i]=true;
    }
    for(int i=1;i<N+1;++i) for(int j=1;j<N+1; j++) Occupied[i][j]=false;
    Occupied[1][1]=true;//entrance
    short last_i=1, last_j=1; // 5% speed gains compared to int
    
    char RequestedPath[N*N];
    cin >> RequestedPath;
 
    FillPaths(N_paths, Occupied, last_i,last_j, N_steps, RequestedPath);//FillPaths(N_paths, current_path, Occupied, last_i,last_j);
    cout << N_paths <<endl;
}