#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <numeric>
#include <algorithm>
using namespace std;

int main(){
    int n, m, h, t;
    cin >> n >> m;
    vector <int> T;
    map <int, int> Freq;
    set <int> H;

    for (int i=0;i<n;i++){
        cin >> h;
        H.insert(h);
        if (Freq.count(h)==0) Freq[h]=1;
        else Freq[h]++;
    }
    for (int i=0;i<m;i++){
        cin >> t;
        T.push_back(t);
    }

    for (auto const t: T){
        if (H.empty()) {
            cout<<"-1\n";
            continue;
        }
        auto it = H.lower_bound(t);
        if (*it==t){
            cout << *it << endl;
            Freq[*it] --;
            if (Freq[*it]==0) H.erase(it);
        }
        if (it==H.end() || (*it>t) ){
            if (it==H.begin()) {
                cout<<"-1\n";
                continue;
            }
            --it;
            cout << *it << endl;
            Freq[*it] --;
            if (Freq[*it]==0) H.erase(it);
        }
    }
}