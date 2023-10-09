/*Each user is trying to maximize their score which means that
if a move of player A helps also player B this should not prevent player A
from doing that move. Nonetheless the game is "zero-sum" and maximizing your
score means minimizing the score of the other player.

We could have two 2D matrices A and B. The A[i,l] element is at the state when
the array of the game starts with element x_i and has length l, what is the maximum
score of the player who playes first from that state. B[i,l] is the maximum
score of the player who playes second. Due to the type of the game it holds
S_il = Sum_{k=i}^{i+l-1} x_k = A[i,l]+B[i,l] (... zero-sum game...).
So we only need to find A[i,l]. Dynamically:
A[i,l] = max(B[i+1,l-1]+x_i, B[i,l-1]+x_{i+j-1})
*/

#include <bits/stdc++.h>
#define int long long
using namespace std;
//const long long inf = 1LL<<60; //1.5e18, max(long long)= 9e18 = 2^63
const int md = 1000000007;


signed main(){    
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int n, S_il,S[5001], l;   
    S[0]=0;
    cin >> n;
    int A[5001][2];//defining an Array A[5001][5001] has memory problems!! 
            //if you want to define A[5001][5001] do it outside the main()
            //By keeping the array as A[5001][2] the code becomes 10 TIMES FASTER!!! (from 0.2 to 0.02)
    l=1;
    for (int i=0; i<n; i++){
        cin >> A[i][l%2];
        S[i+1] = S[i]+A[i][l%2];
    }

    for (l=2; l<=n; l++){
        for(int i=0; i<n-l+1; i++){
            S_il = S[i+l]-S[i];
            A[i][l%2] = S_il - min(A[i][(l-1)%2],A[i+1][(l-1)%2]);
        }
    }
    cout << A[0][n%2];
}