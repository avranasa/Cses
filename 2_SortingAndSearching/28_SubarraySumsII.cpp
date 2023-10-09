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
    unordered_map <int, int> Freq_S;//0.2 seconds faster than the ordered map!
    Freq_S[0] = 1;
    for (int i=0; i<n; i++) {
        cin >> a;
        s += a;
        if (Freq_S.count(s-s_t)>0) ans += Freq_S[s-s_t];
        if (Freq_S.count(s)>0) Freq_S[s] += 1;
        else Freq_S[s] = 1;
    }
    cout << ans;
}