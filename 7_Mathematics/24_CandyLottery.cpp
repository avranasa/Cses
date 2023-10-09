#include<bits/stdc++.h>
using namespace std;

int main(){
    //P(all<=k) = P(all<=k-1) + P(max number is k)
    //ans = sum_over_k  P(max number is k) * k
    int N, K;
    cin >> N >> K;
    vector<double> P_all_less_k;
    P_all_less_k.push_back(0);
    for(int i=1; i<K; i++)
        P_all_less_k.push_back(pow(i/(double)K,N));
    
    P_all_less_k.push_back(1.0);
    double ans = 0.0;
    for (int k=1; k<=K; k++) ans += k*(P_all_less_k[k]-P_all_less_k[k-1]); 

    cout<< setprecision(6)<< fixed;
    cout<< ans;   

}