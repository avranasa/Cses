#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main(){
    int n, m, k, x;
    cin >> n >> m >> k;
    vector <int> A, B;
    for(int i=0; i<n; i++){
        cin >>x;
        A.push_back(x);
    }
    for(int j=0; j<m; j++){
        cin >>x;
        B.push_back(x);
    }
    sort(A.begin(),A.end());
    sort(B.begin(),B.end());

    int j_prev=-1;
    x = 0;
    for(int i=0; i<n; i++){
        for(int j=j_prev+1; j<m; j++){
            if (abs(A[i]-B[j])<=k){
                x ++;
                j_prev = j;
                break;
            }
            if (A[i]<B[j]-k){
                j_prev = j-1;
                break;
            }
        }
    }
    cout << x;    

}