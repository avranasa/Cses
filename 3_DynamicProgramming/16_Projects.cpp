#include <bits/stdc++.h>
using namespace std;
#define int long long

bool cmp_1(pair<int, int> & p, int b){ return p.first < b; }
bool cmp_2(int b, pair<int, int> & p){ return b <= p.first; }

signed main(){
    int n, a, b, m, WAY = 2;
    cin >> n;
    vector<tuple<int,int,int>> P;
    vector<pair<int,int>> MperB;//The i-th element {b,m} contains the maximum money m 
                    //if only the first i projects are considered (projects are sorted
                    //by ending day). All those i projects can be finished before day b.
    vector<pair<int,int>> ::iterator idx;
    for(int i=0; i<n; i++){
        cin >> a >> b >> m;
        P.push_back({b,a,m}); //the sorting we want to be over
                        //the edning time/day. So b gets first
    }
    sort(P.begin(), P.end());
    MperB.push_back({0,0});
    for(int i=0; i<n; i++){        
        tie(b,a,m) = P[i];        
        if (WAY==1) 
            idx = lower_bound(MperB.begin(), MperB.end(), a, cmp_1);
        else if (WAY==2) 
            idx = upper_bound(MperB.begin(), MperB.end(), a, cmp_2);
            
        if (idx==MperB.end()) MperB.push_back({b, MperB.back().second + m});// can start after all previous projects end
        else{//have to consider not doing some other projects (i.e. the ones starting from idx.first day and later)
            idx -- ;
            m = max((*idx).second + m, MperB.back().second);//max_money_if(including i-th project, excluding it)
            MperB.push_back({b,m});            
        }
    }
    cout << MperB.back().second;
}