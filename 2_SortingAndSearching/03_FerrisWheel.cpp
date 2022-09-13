#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//if substituting int with unsigned int it doesn't work in one experiment because in that 
//experiment the last integer is not read????

int main(){
    int n, x, p, N_gond=0;
    vector <int> P;
    cin >> n >> x;
    for (int i=0;i<n;++i){
        //if(i==(n-1)) cout <<"before cin last one";//if unsigned int it will be printed in the 9th test
        cin>>p;
        //if(i==(n-1)) cout <<endl<<"last one";//if unsigned int it will NOT be printed in the 9th test ???
        P.push_back(p);

    }
    sort(P.begin(),P.end());
    int i_start = 0, i_end = n-1;
    while(i_end>=i_start){
        if ((P[i_start]+P[i_end]<=x) && (i_start<i_end)) i_start ++;
        N_gond ++; i_end --;
    }
    cout << N_gond;
}