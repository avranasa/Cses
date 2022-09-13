#include <iostream>
#include <algorithm>

using namespace std;

int main()
{   
    int n;
    cin >> n;
    if ((n<4)&&(n!=1)) cout << "NO SOLUTION";
    else if (n==1) cout <<'1';
    else {
        for (int i=1; i <=n/2;i++ ) cout<<2*i<<' ';
        for (int i=0; i <=n/2;i++ ) cout<<2*i +1<<' ';               
    }
}