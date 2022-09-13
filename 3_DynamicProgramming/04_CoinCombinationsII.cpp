#include <iostream>
using namespace std;

int main(){
    long long n, x ,c, s;
    cin >> n >> x;
    long long mod = (1e9)+7, Coins[n], Sum[x+1]={};
    for (int i=0; i<n; i++){
        cin >> c;
        Coins[i] = c;
    }
    Sum[0]=1;
    for (auto c:Coins){
        s = c;
        while (s<=x){
            if (Sum[s-c]>0){
                Sum[s] += Sum[s-c];
                Sum[s] %= mod;
            }
            s+=1;
        }
    } 
    cout << Sum[x];
}