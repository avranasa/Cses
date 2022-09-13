#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    char x, x_prev=' ';
    int RepAll[] = {0,0,0,0}, Rep = 0, i;
    while (cin>>x){
        if (x == x_prev) Rep += 1;
        else Rep=1;

        if (x =='A') i=0;
        else if (x=='T') i=1;
        else if (x=='C') i=2;
        else if (x=='G') i=3;
        
        if (RepAll[i]<Rep) RepAll[i] = Rep;
        x_prev = x;

    }
    cout << *max_element(RepAll, RepAll+4);
}