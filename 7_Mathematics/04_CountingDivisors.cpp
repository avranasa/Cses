
#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
//#define int long long
using namespace std;
const long long inf = 1LL<<60; //1.5e18, max(long long)= 9e18 = 2^63
const int md = 1000000007;


pair<vector <int>, vector <int>> FindPrimeFactors(int x, vector<int> &Primes){
    //Pr_Un stores all the different prime numbers and Pr_times how many times each prime is a factor
    vector<int> Pr_Un, Pr_times;
    int i = 0, p, p_prev=-1;
    while((x>1) && (i<Primes.size())){
        p = Primes[i];
        if (x%p==0){
            if (p_prev==p) Pr_times.back()++;
            else{
                Pr_times.push_back(1);
                Pr_Un.push_back(p);
            }
            x /= p;
        }
        else i++;
        p_prev = p;
    }
    if (x>1){        
        Pr_times.push_back(1);
        Pr_Un.push_back(x);
    }
    return {Pr_Un, Pr_times}; 
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);  cout.tie(0);
    int n, x, ans;
    cin >> n;
    vector<int> Primes,  Pr_Un, Pr_times;
    array <bool,1001> sieve={false};
    for (int i=2;i<=1000;i++){
        if (sieve[i]) continue;
        Primes.push_back(i);
        for(int k=2*i; k<=1000; k+=i) sieve[k] = true;
    } 

    while(n>0){
        n--;
        cin >> x;
        tie( Pr_Un, Pr_times ) = FindPrimeFactors(x, Primes);
        ans = 1;
        for (auto t: Pr_times) ans*=t+1;
        cout << ans _endl;
    }

}