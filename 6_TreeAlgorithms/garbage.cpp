#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '  
#define _space_ <<' '<<
using namespace std;

int main(){
    int a , b;
    cin >> a >> b;
    for(int const x:{a,b}){
        x += 2;
        cout << x _space_ a _space_ b << endl;
    }
}