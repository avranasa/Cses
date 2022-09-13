#include <iostream>
using namespace std;

int main(){
    int n, s=0;
    cin >> n;
    while (n>1){
        n = n/5;
        s += n;
    }
    cout << s;
}