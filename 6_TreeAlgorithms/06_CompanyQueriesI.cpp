#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '  
#define _space_ <<' '<<
using namespace std;

int main(){    
    ios_base::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);    
    int n, q, boss, middle_b, e, h, pos;
    cin >> n >> q;
    int H[(int) log2(n)+1][n];
    H[0][0]=-1; //0->is the boss and does not have superior
    for(int i=1; i<n; i++){
        cin >> boss;
        H[0][i] = boss-1;
    }
    //building the hierarchy table of powers of 2... i.e. for each employee who is the 2**pos higher boss
    for(int pos=1;(1<<pos)<n; pos++){
        for(int i=0; i<n; i++){
            middle_b = H[pos-1][i];
            H[pos][i]= (middle_b==-1)? -1 : H[pos-1][middle_b];
        }
    }

    //Replies
    for(int i=0; i<q; i++){
        cin >> e >> h;
        if (h>=n) {cout << -1 _endl; continue;}
        pos = 0;
        e--;
        while(h>0){
            if (h%2==1) e = H[pos][e]; 
            if (e==-1) break;
            pos ++;
            h /= 2;
        }
        e = (e==-1) ? -1: e+1;
        cout << e _endl;
    }
}
