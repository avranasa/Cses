#include <iostream>
#include <math.h>
#include <string>
using namespace std;

int main(){
    //2**28 < 1e9 
    int n;
    long long x1 = 1, x2 = pow(10,9)+7;
    cin >> n;
    while (n > 0){
        x1 = x1*pow(2,min(28,n));
        n = n-min(28,n); 
        x1 = x1%x2;
    }     
    cout <<fixed<<x1;
}