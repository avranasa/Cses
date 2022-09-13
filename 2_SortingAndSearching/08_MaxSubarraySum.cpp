#include <iostream>
#include <vector>
using namespace std;

int main(){
    long long n, v;
    vector <long long> V;
    cin >> n;
    for(int i=0;i<n;++i){
        cin >> v;
        V.push_back(v);
    }
    long long S_candidate=-2e16, Smin=0, Smax=-2e15, S=0;
    for(int i=0;i<n; ++i){
        if (Smin >= S) {
            S_candidate = max (S_candidate, Smax-Smin);
            Smin=S;
            Smax=-2e16;//put huge negative numbers... because if S goes extremely low and 
                      // you have for a example a new Smin=-2e15 and you have put Smax=-2e10>>Smin
                      // then even if the S goes up but still much smaller than Smax then as 
                      // a candidate you will assign the false Smax-Smin... with Smax being the 
                      // the wrong initialization.
        }   
        S += V[i];
        Smax = max(Smax,S);
    }
    S_candidate = max (S_candidate, Smax-Smin);
    cout << S_candidate;
}