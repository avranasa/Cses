#include <bits/stdc++.h>

using namespace std;

int main(){
    int m;
    int a, b; 
    cin >> a >> b >> m;
    cout<< (a%m - b%m)%m;
    cout << endl << (a-b)%m;
}