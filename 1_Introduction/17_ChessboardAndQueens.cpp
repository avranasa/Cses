#include <iostream>
#define N 8
using namespace std;


void PlaceQueenInRow(int row, bool Occupied[N][N], bool *col, bool *diag1, bool *diag2, int &N_config){
    for(int j=0; j<N; j++){
        if (Occupied[row][j] || col[j] || diag1[N-1-row+j] || diag2[row+j]) continue;
        if (row == (N-1)) {
            N_config++;
            return;
        }
        col[j] = diag1[N-1-row+j] = diag2[row+j] = true;
        PlaceQueenInRow(row+1, Occupied, col, diag1, diag2, N_config);        
        col[j] = diag1[N-1-row+j] = diag2[row+j] = false;//DO NOT FORGET THIS STEP....ie if one attemp fails to reset the state from which you started the 
    }
}

int main(){
    bool Occupied[N][N], col[N], diag1[2*N-1], diag2[2*N-1];//diag1 from bottom left to up right, diag2 from up left to bottom right
    char c;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin>>c;
            if (c=='.') Occupied[i][j]=false;
            else Occupied[i][j]=true;
        }
    }
    for(int i=0; i<2*N-1;i++){
        diag1[i] = false; //true if occupied and false if it is free
        diag2[i] = false; 
    }
    for(int i=0; i<N; ++i) col[i]=false;
    int N_config=0;
    PlaceQueenInRow(0, Occupied, col, diag1, diag2, N_config);      
    cout << N_config;
}