#include <iostream>
using namespace std;


int main(){
    int n;
    long long ans;
    cin >> n;
    for (long long k=1;k<=n;k++){
        if (k==1) cout<<0<<'\n';
        else if (k==2) cout<<6<<'\n';
        else if (k==3) cout<<28<<'\n';
        else{
            ans = 2*(k*k-3) + 4*(k*k-4) + 2*(k*k-5)*(k-4);
            ans += 2*(k*k-5) + 2*(k-4)*(k*k-7) + (k*k-9)*(k-4)*(k-4)/2;
            cout << ans<<'\n';           
        }
    }
}
