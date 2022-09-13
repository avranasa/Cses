#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{   
    long int x ;
    for ( cin >> x ; x != 1 ; x = (x%2 == 0) ? x/2 : x*3+1)    cout << x<< " ";
    cout <<x << endl;
}