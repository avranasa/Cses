#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
#define int long long
using namespace std;
const long long inf = 1LL<<60; //1.5e18, max(long long)= 9e18 = 2^63
const int md = 1000000007;

//md (1000000007) is prime

int exp_modulo(int a, int b, int m){
    int ans;
    if ((b==0)||(a==1)) ans = 1;
    else if (a==0) ans = 0;
    else{
        ans = 1;
        while(b!=0){
            if (b%2==1) ans = (ans*a)%m;
            a = (a*a)%m;                
            b = b >> 1 ; 
        }
    }   
    return ans;
}


signed main(){
    int n, p, a, num_f1=1, num_f2=1, num_f2_div2=1, sum_f=1, inv_md_p, K, prod_f=1;
    cin >>n;
    vector <int> P, A;
    //Euler's totient of  md=1,000,000,007 and md-1
    //md is prime and md-1 prime factors are 2*500,000,003
    int euler_tot_md = md-1;

    bool div2_notDone = true;
    for (int i=0; i<n; i++){
        cin >> p >> a;
        P.push_back(p);
        A.push_back(a);   
        num_f1 = (num_f1*(a+1)) % md; 
        //num_f2 = (num_f2*(a+1)) % (md-1); // (LINE A)to be used for prod_f... fermat's little theorem 
        if (div2_notDone && (a+1)%2==0)  {
            num_f2_div2 = (num_f2_div2*(a+1)/2) % (md-1);
            div2_notDone = false;
        }
        else num_f2_div2 = (num_f2_div2*(a+1)) % (md-1);

        K = exp_modulo(p, a+1, md)-1; 
        if (K<0) K += md;
        inv_md_p = exp_modulo(p-1, euler_tot_md-1, md);
        sum_f *= (K*inv_md_p)%md; 
        sum_f %= md;
    }
    
    for (int i=0; i<n; i++){
        //SOS! 2 and md-1 are NOT coprimes so an I = inverse_{md-1}(2) does not exist!
        //Therefore you can NOT use again the trick (A[i]*num_f2*I)%(md-1)
        //a = (A[i]*num_f2/2)%(md-1); <== this (together with line A) also gives (mathematically) wrong results!
        // The following solution that uses div2_notDone so as to handle the division with 2.
        if (div2_notDone) a = (num_f2_div2*A[i]/2)%(md-1);
        else a = (A[i]*num_f2_div2)%(md-1);
        //A more elegant solution is https://usaco.guide/problems/cses-2182-divisor-analysis/solution using 
        //a elegant way of building dynamically the prod_f by using previous step prod_f and P[i]^(A[i]*(A[i]+1)/2).
        //(in the site P[i] is x_i and A[i] is k_i... note that k_i*(k_i+1) is an even number )
        //Also note that my solution is not dynamic programming as the num_f2_div2 is computed using all A[i] but 
        //in the site the prod_f2 in step i is computed using only the first i factors.


        K = exp_modulo(P[i], a, md) ; 
        prod_f = (prod_f * K) % md;
    }
    cout << num_f1 _space_ sum_f _space_ prod_f;
    
}