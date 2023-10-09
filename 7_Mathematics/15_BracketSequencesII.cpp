//Check https://brilliant.org/wiki/catalan-numbers/ https://math.stackexchange.com/questions/337842/simplifying-catalan-number-recurrence-relation 
// https://math.mit.edu/~rstan/transparencies/china.pdf
#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
#define int long long
using namespace std;
const int md = 1000000007;

int modpow(int x, int n, int p){
    int res=1; 
    x%=p;
    while(n>0){
        if (n%2) res= (res*x)%p; 
        n=n>>1; 
        x=(x*x)%p;
    }
    return res;
}


int modcatalan(int n, int p){
    if ((n==0) || (n==1)) return 1;
    int f1 = 1, f2_inv, f3_inv;
    //computing f1/(f2*f3) with f1=(2n)!, f2=(n+1)!, f3=(n)!
    for (int x=1; x<=2*n; x++){
        f1 = (f1*x)%md;
        if (x==n) f2_inv=modpow(f1, md-2, md);
        if (x==n+1) f3_inv=modpow(f1, md-2, md);
    }
    return ((f1*f2_inv)%md * f3_inv)%md;
}

int modcatalan_v2(int n, int k, int p){
    if ((n==0) || (n==k)) return 1;
    int f1 = 1, f2_inv, f3_inv;
    //computing (k+1)*f1/(f2*f3) with f1=(2n-k)!, f2=(n+1)!, f3=(n)!
    for (int x=1; x<=2*n-k; x++){
        f1 = (f1*x)%md;
        if (x==n-k) f2_inv=modpow(f1, md-2, md);//if  (n==k) you already returned 1
        if (x==n+1) f3_inv=modpow(f1, md-2, md);
    }
    f1 = (f1*(k+1))%md;
    return ((f1*f2_inv)%md * f3_inv)%md;
}

signed main(){
    int n, k=0, f1=1, f2_inv, f3_inv, Cn_k;    
    string pr;
    cin >> n >> pr;
    for(char c:pr){
        if (c=='(') k += 1;
        else if (c==')') k -= 1;
        if (k<0) {cout << 0; return 0;}
    }
    
    if ((n%2==1) || (k<0) || (n<pr.size()) || (k>n/2)) {
        cout << 0; 
        return 0;
        }    
    /*WRONG
    int n_eff = n - pr.size() + k; //pr.size() and k are either both odd or both even
    //Computing the possible valid ways to put n_eff/2 "(" and 
    //n_eff/2 ")" but starting with k "(". This is equal to 
    // Catalan(n_eff/2) / Catalan(k)
    int A = modcatalan(n_eff/2, md), B = modcatalan(k,md);
    cout <<k _space_ pr.size() _space_ n_eff _space_ A _space_ B _endl;
    int B_inv = modpow(B, md-2, md);
    cout << ( A * B_inv )%md;
    */
   /*WRONG
   int n_eff = n - pr.size() -k; //pr.size() and k are either both odd or both even
    //Computing the possible valid ways to put n_eff/2 "(" and 
    //n_eff/2 ")" but starting with k "(". This is equal to 
    // Catalan(n_eff/2) / Catalan(k)
    int A = modcatalan(n_eff/2, md), B = modcatalan(k,md);
    cout << ( A * B )%md;
    */
   int n_eff = n - pr.size() + k;
   cout << modcatalan_v2(n_eff/2, k, md);
}