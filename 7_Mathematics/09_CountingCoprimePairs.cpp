#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
#define int long long
using namespace std;
//the maximum prime factors a number x<10^6 can have is 6 since 2*3*5*7*11*13*17*23 >  10^6

signed main(){
    //stores all given numbers and their frequency
    int WAY=3;
    int n, x, p, max_x=0, x_red, not_coprimes=0, add_pairs;
    cin >> n;
    map<int,int> X_f; 
    for (int i=0; i<n; i++){
        cin >> x;
        if (X_f.find(x)==X_f.end()) X_f[x] = 1;
        else X_f[x] += 1;
        if (x>max_x) max_x = x;
    }
    if (WAY==1){
        //Find all primes up to 1000... 1000*1000 is the maximum value of a given x
        bool P_bool[1001]={false}; 
        vector<int> P;
        for (int i=2; i<1001; i++){
            if (P_bool[i]) continue;
            P.push_back(i);
            for(int j=2*i; j<1001; j+=i) P_bool[j] = true;
        }

        //compute the numbers of pairs that are NOT coprimes
        vector<int> P_X[P.size()] ;//for each prime it saves all x that have that prime as a factor
        for(auto const&[x, f]: X_f){
            add_pairs = 0;
            x_red = x;
            if (x==1) continue; //1 is coprime with every integer so does not contribute to "not_coprimes"
            set<int> NotCoprimes;
            for(int i=0; i<P.size(); i++){   
                p = P[i];         
                if (x_red%p != 0) continue; 
                while (x_red%p==0) x_red /= p;  
                for (auto x_pair: P_X[i]){
                    if (NotCoprimes.count(x_pair)>0) continue;
                    NotCoprimes.insert(x_pair);
                    add_pairs += X_f[x_pair];
                }          
                P_X[i].push_back(x);  
                while (x_red%p==0) x_red /= p; //not obligatory but it helps breaking earlier the loop
                if (x_red<p) break;
            }
            not_coprimes += f*add_pairs + f*(f-1)/2;//f*(f-1)/2 because two numbers equal to each other are not coprime
            //case that a new prime (bigger than 1000) has to be included
            //Actually this step is not necessary since if x_i and x_j that 
            //are both smaller than 10^6 have both a prime factor p>1000 then
            //x_i==x_j.
            /*
            if (x_red>1) {
                vector< int > X={x};
                P_x[x_red] = X;
            } 
            */        
        }
    }
    else if (WAY==2){
        bool P_bool[1000001] = {false}; 
        int k, prod_p ;
        map<int,vector<int>> X_P;//for each X all the prime factors
        map<int,int> N_p; //for each prime factor and product of primes it counts the number of x that those x divide.
        for (int i=2; i<1000001; i++){
            if (P_bool[i]) continue;
            for(int j=2*i; j<1000001; j+=i) P_bool[j] = true;
            for(int j=i; j<max_x+1; j+=i) {
                if (X_f.find(j)==X_f.end()) continue;
                if (X_P.find(j)==X_P.end()){
                    //i is the first prime number of j we found 
                    vector <int> P={i};
                    X_P[j] = P;
                    if (N_p.find(i)==N_p.end()) N_p[i] = X_f[j];
                    else N_p[i] += X_f[j];
                }
                else {
                    //i is not the first prime number of j we found 
                    k = X_P[j].size();
                    for(int r=0; r< (1<<k); r++){
                        prod_p = i;
                        for(int pos=0; pos<k; pos++){
                            if (r & 1<<pos) prod_p *= -1 * X_P[j][pos]; 
                        }
                        if (N_p.find(prod_p)==N_p.end()) N_p[prod_p] = X_f[j];
                        else N_p[prod_p] += X_f[j];
                    }
                    X_P[j].push_back(i);
                }  

            }
        }
        for(auto const&[p, n_p]:N_p ){
            add_pairs = n_p*(n_p-1)/2;
            not_coprimes += (p>0) ? add_pairs : -add_pairs;
        }
        
    }
    else if (WAY==3){
        //Same idea as WAY 2 but finding N_p map faster. First find all prime numbers from 1 to 1000.
        //Then using those find all the factors of the input numbers x (i.e. the X_P map of WAY=2). 
        //In this way actually you do not need to compute all X_P but for every number x the P_per_x is
        //enough. Finally compute N_p.

        bool P_bool[1001]={false}; 
        vector<int> P;
        for (int i=2; i<1001; i++){
            if (P_bool[i]) continue;
            P.push_back(i);
            for(int j=2*i; j<1001; j+=i) P_bool[j] = true;
        }

        int k, prod_p ;
        map<int,int> N_p; //for each prime factor and product of primes it counts the number of x that those x divide.
        for(auto const&[x, f]: X_f){
            if (x==1) continue; //1 is coprime with every integer so does not contribute to "not_coprimes"
            x_red = x;
            vector <int> P_of_x;//prime factors of x
            for(auto p: P){      
                if (x_red%p != 0) continue; 
                while (x_red%p==0) x_red /= p;           
                P_of_x.push_back(p);  
                while (x_red%p==0) x_red /= p; //not obligatory but it helps breaking earlier the loop
                if (x_red<p) break;
            }
            if (x_red>1) P_of_x.push_back(x_red);
            
            k = P_of_x.size();
            for(int r=1; r< (1<<k); r++){
                prod_p = 1;
                for(int pos=0; pos<k; pos++){
                    if (r & 1<<pos) prod_p *= -1 * P_of_x[pos]; 
                }
                if (N_p.find(prod_p)==N_p.end()) N_p[prod_p] = f;
                else N_p[prod_p] += f;
            }
        }
        for(auto const&[p, n_p]:N_p ){
            add_pairs = n_p*(n_p-1)/2;
            not_coprimes += (p>0) ? -add_pairs : +add_pairs;
        }
        
    }
    cout << n*(n-1)/2-not_coprimes ; 
}
