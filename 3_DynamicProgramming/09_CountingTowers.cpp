#include <iostream>
using namespace std;
#define MOD 1000000007


int main(){
    // Assume that the tower of height n-1 has x1 ways to be formed with the highest row be one continuous block
    // and x2 ways with the highest one being separated into two columns. Then you can find the x1 and x2 of the 
    // tower with height n by thinking that you can either extend the highest columns for increasing the height of
    // the tower or put a "stop" and then new separate rectangles/squares.
     
    long long t, n, ans_2columns, ans_1column, temp;
    cin >> t;
    for (int i=0; i<t; i++){
        cin >> n ;
        ans_2columns = 1;
        ans_1column = 1;
        for(int j=1; j<n; j++ ){
            temp = (2*ans_1column + ans_2columns)%MOD;
            ans_2columns = (ans_1column + 4*ans_2columns)%MOD;
            ans_1column = temp;
        }        
        cout << (ans_2columns + ans_1column) % MOD << endl;
    }
}