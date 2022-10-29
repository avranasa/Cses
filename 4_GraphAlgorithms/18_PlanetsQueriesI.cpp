#include <iostream>
using namespace std;

int main(){    
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, q, t, x, k, F=30, Method=2;
    cin >> n >> q;
    int Tele[F][n], ans[q]; //the (i,j) element represents the planet you land after 2**(i+1) steps 
                    //starting from j-th planet...2^F>10^9 so 29 steps are enough. 
    //bool Sink[n]; //a bit faster without it
    for (int i=0; i<n; i++) {
        cin >> t; 
        Tele[0][i] = t-1;
        //Sink[i] = (i==t-1);
    }
    for (int k=1; k<F; k++)
        for(int i=0; i<n; i++) 
            Tele[k][i] = Tele[k-1][Tele[k-1][i]]; 
    
    
    
    for (int i=0;i<q;i++){
        cin >> x >> k; 
        x--; t = 0;
        if (Method == 1){
            for (int i=F;i>=0; i--){// a bit faster this method (about 0.01 sec)
                if (k & (1<<i)) {
                    x = Tele[i][x];
                    //if (Sink[x]) break;
                }
            }
        }
        else if (Method == 2){
            while (k>0){
            if (k%2) x = Tele[t][x]; 
            //if (Sink[x]) break;
            t++; k /= 2;
            }
        }     
        ans[i] = x+1;
        //cout << x+1 << endl; //slower (0.05sec) than gathering all the answers and after doing the "cout"(outside the loop.)
    }
    for(int i=0; i<q; i++) cout << ans[i] << endl; 
}