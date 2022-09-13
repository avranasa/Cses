#include <iostream>
using namespace std;

int main(){
    long long n, x ,c;
    cin >> n >> x;
    long long mod = (1e9)+7, Coins[n], Sum[x+1]={};
    for (int i=0; i<n; i++){
        cin >> c;
        Coins[i] = c;
    }
    for (long long s=1;s<=x; s++){
        for (auto c:Coins){
            if (s==c) Sum[s] += 1; 
            else if (s-c > 0) Sum[s] += Sum[s-c];
        } 
        Sum[s] %= mod;
    }
    cout << Sum[x];
}