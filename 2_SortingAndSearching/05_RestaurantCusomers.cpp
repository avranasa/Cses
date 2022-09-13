#include <map>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int main(){
    int a, b,  max_cust = 0, n;
    cin >> n;
    vector <int> A(n), B(n);
    for (int i=0; i<n; i++){
        cin >> a >> b;
        A[i]=a; B[i]=b;
    }
    sort (A.begin(),A.end());
    sort (B.begin(),B.end());//Don't care to keep the ordering, i.e. which customer left
                            //but just that a customer left

    int i_in=0, i_out=0, n_cust=0;
    for (int t=0;t<2*n;t++){
        if ((A[i_in]<B[i_out]) && (i_in<n)){ ///SOS YOU MUST CHECK IF YOU CHECKED ALL INCOMING CUSTOMERS
                                             // and stop checking i_in. C++ allows to access even bigger
                                            // than the size index!!! e.g A[n], A[n+1], ...
            //customer in
            n_cust++; 
            i_in++;
        }
        else{
            //customer out
            n_cust--; 
            i_out++;
        }
        max_cust = max(max_cust, n_cust);     
    }
    cout << max_cust;
}