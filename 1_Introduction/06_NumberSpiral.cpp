#include <iostream>
#include <algorithm>

using namespace std;

int main()
{   
    long long N, i, j, x;
    cin >> N;
    for (int k=0;k<N;k++){
        cin >> i >> j;
        if (i>j) (i%2==0) ? cout<< i*i-j+1 : cout<<(i-1)*(i-1)+j;
        else (j%2==0) ? cout<<(j-1)*(j-1)+i : cout<< j*j-i+1;
        cout << '\n';
    }
}