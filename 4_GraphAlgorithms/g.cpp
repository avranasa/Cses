#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
using namespace std;

int main(){
    int m ;
    cin >> m;
    int Range[m];
    iota(Range,Range+m,0);
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(Range, Range+m, default_random_engine(seed));
    for (int i=0; i<m; i++) cout << Range[i];
}