#include <iostream>
#include <vector>
#include <cmath>
#include <bitset>
using namespace std;


long long inner_prod(vector <long long> a, int b){
    long long ans=0;
    for(int i=0;i<a.size();++i) ans+=a[i]* (2*((b>>i)& 1) -1);
    return ans;
} 

int main(){
    long long n, x, dif=-1, new_dif;
    cin >> n;
    vector <long long> P(n);
    for(int i=0; i<n;i++){
        cin >> x;
        P[i] = x;
    }
    if (n==1) cout << P[0];
    else{
        for (long long b=1; b< (1<<n); ++b ){
            new_dif = abs( inner_prod(P,b) );
            if (dif == -1) dif = new_dif;
            else dif = min(new_dif,dif);
        }
        cout << dif;
    }
    
}