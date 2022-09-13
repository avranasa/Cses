#include <iostream>
#include <algorithm>

using namespace std;

int main()
{   
    int N, x, x_prev;
    long long ans;
    cin >> N;
    for (int i=0; i<N; i++){
        cin >> x;
        if (i==0) {
            x_prev = x;
            continue;
        }
        if (x_prev > x) ans+= x_prev-x;
        else x_prev = x;
    }
    cout << ans;
}