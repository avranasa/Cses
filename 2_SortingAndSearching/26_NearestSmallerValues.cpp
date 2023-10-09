#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int n;
    cin >> n;
    int X[n], Ans[n], j;
    for (int i=0; i<n; i++){
        cin >> X[i];
        if (i==0) {Ans[0] = -1; continue; }
        j = i-1;
        while(j>=0){
            if (X[j]<X[i]) break;
            j = Ans[j];
        }     
        Ans[i] = j;
    }
    for (int i=0; i<n; i++) cout << Ans[i]+1 _space ;

    /* The implemented solution works very fast. Another fast 
    solution would be processing X[] so as to answer fast queries
    about minimum of a range. Then finding the nearest smaller value 
    of the i-th element X[i] would be making a binary search over the previous 
    elements (i.e. X[0:i]). At each iteration of the binary search we check 
    the minimum  values of two ranges (X[right:i] and X[left:i] with right>left) 
    and depending if the minimum value  of the "right" range is smaller 
    than X[i] we choose this range to dichotomize in the next iteration, 
    other wise we choose the left range.
    */
}