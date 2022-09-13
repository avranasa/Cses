#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;
 
int main()
{
    // declaration of vector container
    //set<string> myvector{ "This", "is",  "Geeksforgeeks" };
    set <int> myvector ;
    myvector.insert(0);
    myvector.insert(1);
 
    // using begin() to print vector
    for (auto it = myvector.crbegin();  it != myvector.crend(); ++it)         cout << ' ' << *it;
    return 0;
}