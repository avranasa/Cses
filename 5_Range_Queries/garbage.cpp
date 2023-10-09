

#include <bits/stdc++.h>
#define ff first
#define ss second
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
//#define int long long
using namespace std;
const int md = 1000000007;
int main(){
    int q, a, b;
    cin >> q;
    vector <pair<int, int>> Q;
    vector <int>F;
    for (int i=0; i<q; i++){
        cin >> a >> b;
        Q.push_back({a,b});
        F.push_back(a);
    }    
    vector<size_t> idx(Q.size());
    iota(idx.begin(), idx.end(), 0);
    stable_sort(idx.begin(), idx.end(), [&F](size_t i1, size_t i2) {return F[i1] < F[i2];});

    //q=0;
    //for (int i=0; i<q; i++) cout << idx[i] << " ";
    //cout << endl;
    
    //for (int i=0; i<q; i++) cout << Q[idx[i]].ff << " " << Q[idx[i]].ss << endl;
}

