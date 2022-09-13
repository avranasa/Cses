#include <iostream>
#include <set>

using namespace std;

int main(){
    int n,x;
    set <int> S;
    cin >>n;
    for(int i=0; i<n; i++){
        cin >> x;
        S.insert(x);
    }    
    cout << S.size();
}