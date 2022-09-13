#include <iostream>
#include <set>

using namespace std;

int main(){
    int n, x;
    cin >> n;
    set <int> S;//its cardinality is the number of rounds needed. And the element represent the biggest value obtained in each round
    for (int i=0; i<n; i++){
        cin >> x;
        S.erase(x-1);
        S.insert(x);
    }
    cout << S.size();
}