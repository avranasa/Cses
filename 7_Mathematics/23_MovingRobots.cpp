#include<bits/stdc++.h>
using namespace std;
#define double long double 


void matmul(double A[64][64], double B[64][64], double C[64][64]){
    for(int i=0; i<64; i++)
        for (int j=0; j<64; j++){
            C[i][j] = 0.0;
            for(int k=0; k<64; k++) 
                C[i][j] += A[i][k]*B[k][j];
        }
}

int main(){
    double P[64][64]={0};//transition matrix, (k,l) element is the probability going from 
                 // the square (k//8,k%8) to the element (l//8,l%8)
    double P_k[64][64]={0};//transition matrix after k moves    
    for(int i=0; i<64; i++) P_k[i][i] = 1.0;
    int k, curr_p;
    double p_m;
    //initialization of P
    for (int i=0; i<8; i++){//row
        for (int j=0; j<8; j++){//column
            //starting from (i,j) square
            p_m = 4.0; //possible moves
            if (i==0 || i==7) p_m -= 1;
            if (j==0 || j==7) p_m -= 1;
            curr_p = i+j*8; //current position
            if (i!=0) P[curr_p][curr_p-1] = 1.0/p_m;
            if (i!=7) P[curr_p][curr_p+1] = 1.0/p_m;
            if (j!=0) P[curr_p][curr_p-8] = 1.0/p_m;
            if (j!=7) P[curr_p][curr_p+8] = 1.0/p_m;                        
        }
    }

    cin >> k;
    double P_temp[64][64]={0};
    //create P**k
    while (k>0){
        if (k%2==1) {
            matmul(P_k, P, P_temp); 
            swap(P_k,P_temp);
        }
        matmul(P, P, P_temp);
        swap(P,P_temp);
        k /= 2;        
    }
    
    //The initial position can be represented as an identity matrix I[64][64] as where
    //the element (i,j) is refering to the i-th robot at the (j//8,j%8) position. 
    //Multiplying I@P_k = P_k gives the probability of each robot after k moves being
    //at each position...
    double P_empty[64], ans=0;//Probability of each square being empty
    for (int i=0; i<64; i++){//iterate over all positions
        P_empty[i] = 1;
        for (int j=0; j<64; j++){//iterate over all robots
            P_empty[i] *= (1-P_k[j][i]);
        }
        ans += P_empty[i];
    } 
    cout<< setprecision(6)<< fixed;
    cout<< ans;
}