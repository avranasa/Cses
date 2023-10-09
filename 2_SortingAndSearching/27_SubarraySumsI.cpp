#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
#define int long long
using namespace std;

signed main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int n, s_t, a, s=0, ans=0;
    cin >> n >> s_t;
    unordered_set <int> S;
    S.insert(0);
    for (int i=0; i<n; i++) {
        cin >> a;
        s += a;
        ans += S.count(s-s_t);
        S.insert(s);
    }
    cout << ans;
}