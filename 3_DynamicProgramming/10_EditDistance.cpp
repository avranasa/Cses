#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
#define int long long
using namespace std;
const long long inf = 1LL<<60; //1.5e18, max(long long)= 9e18 = 2^63
const int md = 1000000007;

//... A good testing example: JPJA and FJPJ
signed main(){
    //Bad attempt
    string s1, s2;
    cin >> s1 >> s2;//the >> drops the new_line character of the input
    if (s1.size()>s2.size()) swap(s1,s2); //assume first string is smaller
    int N1 = s1.size(), N2 = s2.size(), add;
    int D[N1][N2];//A[i][j] gives the distance if only the first (i+1) characters
                  //of s1 word and (j+1) characters of s2 word are considered.
    //P.S. You could decrease the necessary memory by using only two columns (or rows.)

    for (int i=0; i<N1; i++){
        for (int j=0; j<N2; j++){
            add = s1[i]!=s2[j];
            //Let "c" being the j-th character of s2
            //Corner cases
            if (j==0 && i==0) D[i][j] = add;//"c" is the first character in first position
            else if (j==0) D[i][j] = min(i+add, D[i-1][j]+1);//"c" is the first character
            else if (i==0) D[i][j] = min(j+add, D[i][j-1]+1); //"c" is the first position
            if (i==0 || j==0) continue;

            //Regular cases
            D[i][j] = min({D[i-1][j]+1, D[i-1][j-1]+add, D[i][j-1]+1});// The cases are
            //using "c" in: A)[0,...j-1] position, B) in j-th position, C)not using it.
        }
    }
    cout << D[N1-1][N2-1];
}