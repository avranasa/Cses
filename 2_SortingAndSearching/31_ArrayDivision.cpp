/*Wrong approaches??
-Trying to solve first the problem for k and then use that solution for breaking the array
into 2*k subarrays... Counterexample: Imagine that 1 3 2 2 3 is given. Then for k=2
the solution is (1 3 2)(2 3) and for k=4 (1)(3)(2 2)(3)...=> i.e. for k=4 you put the 2-2
in the same subarray but not for k=2...

-If you have (k-1) pointers that split the array into k subarrays then try to optimize 
the first pointer while keeping the rest fixed, then the second,.... After you optimized
all of them repeat again the procedure and optimize the first pointer, the second,...
Finish when there is no change of the position of the pointers.... Counterexample:
Imagine you are given 5 6 3 3 3 3 and k=3 (i.e. two pointers). You keep the last/second pointer
before the last element (i.e. 5 6 3 3 3 |3 ) and you optimize the first pointer. 
You get 5 6 | 3 3 3 | 3. Then you optimize the second and you get 5 6 | 3 3 | 3 3. No 
repeatition will change that "solution". But the optimal one is 5 | 6 3 |3 3 3.

*/

#include <bits/stdc++.h>
#define int long long
using namespace std;
  
bool feasible(int X[], int n, int k, int max_s){
    //checks if there exists a feasible solution where the max sum
    //is equal or smaller than max_s. In otherwise when returned 
    //true it means max_s could be reduced
    int j=1, s=0;
    for(int i=0;i<n;i++){
        s+=X[i];
        if (s>max_s){
            j++;
            if ((j>k)||(X[i]>max_s)) return false;
            s = X[i];
        }  
    }
    return true;
}

signed main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int k, n, ans_s, lower_s=1e15, upper_s=0;
    cin >> n >> k;
    int X[n];
    for(int i=0;i<n;i++) {
        cin >> X[i];
        lower_s = min(lower_s,X[i]);
        upper_s += X[i];
    }
    while(lower_s<upper_s){
        ans_s = (lower_s+upper_s)/2;
        if (feasible(X,n,k,ans_s)) upper_s=ans_s;
        else lower_s = ans_s+1;
    }
    cout <<upper_s;//here lower_s==upper_s
}