#include <iostream>
using namespace std;

int main(){
    long long k, N, k_init;
    cin >> N;
    if (N*(N+1)/2%2 == 1) cout << "NO";
    else{
        cout << "YES"<<'\n';
        if (N%2==0){
            cout << N/2 << '\n';
            k_init = 1;
        }
        else{
            cout << (N/2+1) << "\n1 ";
            k_init = 2;
        }
        int i = 0;// when 0 3 it prints else it does not
        for(k=k_init; k<=N; k++){
            if ((i==0)||(i==3)) cout <<k <<' ';
            i = (i+1)%4;        
        }   
        cout << '\n'<< N/2 << '\n';
        i=0;
        for(k=k_init; k<=N; k++){
            if ((i==1)||(i==2)) cout <<k <<' ';
            i = (i+1)%4;        
        }              
    }
}