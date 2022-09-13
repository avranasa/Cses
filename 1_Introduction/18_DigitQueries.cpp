#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(){
    int q;
    bool FoundNumDigits;
    unsigned long long k, d, f, base, Lim, n;
    string x_str;
    vector<unsigned long long> D;//In n-th position it maps the length of string
                                //needed for all the numbers with at most (n+1 ?) digits
    
    base = 1;  f = 0;  d = 0; n = 0;
    D.push_back( 0 );
    Lim = 1000000000000000000;//10**18   
    while(d<Lim){
        n ++;
        f = 9* base;// number of n-digits numbers
        base *= 10;
        d += n*f;
        D.push_back( d );
    }
    cin >> q;
    for(int i=0;i<q;++i){
        cin >> k;
        FoundNumDigits = false; n=0; base = 1;
        while((!FoundNumDigits)||(n>=D.size())){
            n++; 
            if(k<=D[n]) FoundNumDigits = true;
            if (n>1) base*=10;
        }
        if (!FoundNumDigits) n++;
        if (n==1) cout <<k<<endl;
        else{ 
            x_str = to_string( base + (k-D[n-1]-1)/n );
            cout << x_str[(k-D[n-1]-1)%n] <<endl;    
        }     
    }
}