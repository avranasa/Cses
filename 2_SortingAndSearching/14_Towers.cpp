#include <iostream>
#include <set>

using namespace std;

int main(){
    int n, k, n_towers;
    multiset <int> towers;
    cin >> n;
    for (int i=0; i<n; i++){
        cin >> k;
        auto t=towers.upper_bound(k);
        if (t == towers.end()) n_towers++;
        else towers.erase(t);
        towers.insert(k);
    }
    cout << towers.size();
}