#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

int main(){
    int n, indx, r;
    cin >> n;
    vector <bool> s(n,false);
    //Change of digit in position: 1,2,1,3,1,2,1,4,1,2 ,1 ,3 ,1 ,2 ,1 ,5 ,...
    //for iteration:               1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,...
    for (int i=1 ;i<=pow(2,n); i++){
        for (auto x:s) cout <<x;  
        cout<<'\n'; 
        indx = 0;
        r = i;
        while (r%2==0){
            indx ++;
            r /= 2;            
        }
        s[indx] = !s[indx];
    }  
}