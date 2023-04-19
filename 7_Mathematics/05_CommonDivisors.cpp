//1st way: You could use the Euclids alrorithm to find all GCD for each pair and then output the maximum one.
//Maybe improve the speed by first sorting and choose first the pairs of the bigger numbers and if you 
//find a big number X as GCD then consider pairs of numbers that both are bigger than X.

//2nd way: find all the prime between 10^3 (=sqrt(10^6)) and using them find all the factors for each number.
//Whenever you find a factor of a number that you have not seen it yet add it in a set. When you see a 
//factor that is already in the set then see if it is bigger than the for the time being maximum 
//stored GCD and if yes replace it.


#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
//#define int long long
using namespace std;
const long long inf = 1LL<<60; //1.5e18, max(long long)= 9e18 = 2^63
const int md = 1000000007;

int Euclid_gcd(int a, int b){
    if (b==0) return a;
    return Euclid_gcd(b, a%b);
}


pair<vector <int>, vector <int>> FindPrimeFactors(int x, vector<int> &Primes){
    //Pr_Un stores all the different prime numbers and Pr_times how many times each prime is a factor
    vector<int> Pr_Un, Pr_times;
    int i=0, p, p_prev=-1;   
    while(x>1){
        p = Primes[i];
        if (x%p==0) {
            if (p==p_prev) Pr_times.back()++;
            else {
                Pr_Un.push_back(p);
                Pr_times.push_back(1);
            }
            x /= p;
        }
        else if (i<Primes.size()-1) i++;
        else break;
        p_prev = p;
    }    
    if (x>1)  {
        Pr_Un.push_back(x);
        Pr_times.push_back(1);
    }
    return {Pr_Un, Pr_times}; //If Primes are sorted then also PrimeFactors are sorted
}

vector <int> FindAllFactors(int x, int m, vector<int> &Primes){
    //returns an vector with all the factors of x bigger than m (... so also bigger than 1)
    vector<int>  Pr_Un, Pr_times, AllFactors;
    tie(Pr_Un, Pr_times) = FindPrimeFactors(x, Primes);
    int N_comb = 1, f, i_remain;
    for (auto t: Pr_times) N_comb *= t + 1;
    for(int i=0; i< N_comb; i++) {
        f=1;
        i_remain = i;
        for (int k=0; k<Pr_Un.size(); k++){
            f *= pow(Pr_Un[k],  i_remain % (1+Pr_times[k])) ; 
            i_remain /= (1+Pr_times[k]);
        }
        if (f>m) AllFactors.push_back(f);        
    } 
    return AllFactors;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);  cout.tie(0);
    int WAY = 2;
    int n, x, max_gcd=1 ;
    vector <int> X;
    cin >> n;
    for (int i=0; i<n; i++){
        cin >> x; 
        X.push_back(x);
    }
    
    if (WAY==1){
        sort(X.rbegin(), X.rend());
        for(int i=0; i<n-1; i++){
            for(int j=i+1; j<n; j++){
                if (max_gcd>=X[j]) break;
                max_gcd = max(max_gcd, Euclid_gcd(X[i],X[j]));
            }
        }
    }
    else if (WAY==2){
        vector<bool> sieve(1001, false);
        vector <int> Primes;
        for(int i=2; i<=1000; i++){
            if (sieve[i]) continue;
            Primes.push_back(i);
            for(int j=2*i; j<=1000; j+=i) sieve[j]=true;
        }
        //unordered_set <int> F;
        array <bool,1000001> F={false}; //Faster by 0.15 sec compared to unordered_set
        for(auto x : X){
            if (x<=max_gcd) continue;
            for (const auto & f: FindAllFactors(x, max_gcd, Primes)){
                //if (F.count(f)>0) max_gcd = max(max_gcd,f);//if F is unordered_set
                //else F.insert(f);
                if (F[f]) max_gcd = max(max_gcd,f);//if F is unordered_set
                else F[f]=true;
            }                
        }
    }   
    else if (WAY==3){
        //Almost the same as previous way but reusing array F with all the factors 
        vector<bool> sieve(1001, false);
        vector <int> Primes, PrimeFactors;
        for(int i=2; i<=1000; i++){
            if (sieve[i]) continue;
            Primes.push_back(i);
            for(int j=2*i; j<=1000; j+=i) sieve[j]=true;
        }        
        array <bool,1000001> F={false}; 
        vector <int> Pr_Un, Pr_times;
        int f, p_prev, N_comb, i_remain;
        for(auto x : X){
            if (x<=max_gcd) continue;
            tie(Pr_Un, Pr_times) = FindPrimeFactors(x, Primes);//Both Primes and PrimeFactors are sorted   
            N_comb = 1;
            for (auto t: Pr_times) N_comb *= t + 1;
            for(int i=0; i< N_comb; i++) {
                f=1;
                i_remain = i;
                for (int k=0; k<Pr_Un.size(); k++){
                    f *= pow(Pr_Un[k],  i_remain % (1+Pr_times[k])) ; 
                    i_remain /= (1+Pr_times[k]);
                }
                if (F[f]) max_gcd = max(max_gcd,f);
                else F[f]=true;
            }              
        }
    }   
    cout << max_gcd;     
}