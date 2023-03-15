#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

long long cost(vector<long long> &V, long long thr){
    long long ans = 0;
    for(auto x:V) ans += abs( x-thr );
    return ans;
}

int main(){
    int METHOD = 2;
    long long x, n, x_min=2e9, x_max=-2e9;
    cin >> n;
    vector <long long> V;
    for (int i=0; i<n; i++){
        cin >> x;
        V.push_back(x);
        x_min = min(x,x_min);
        x_max = max(x,x_max);
    }
    if ( METHOD== 1){
        if (n==1){
            cout << '0';
            return 0;
        }

        long long x_left=x_min, x_right=x_max, x_center = x_min+ (x_max-x_min)/2, Dx = x_max-x_min;
        long long y_left, y_right, y_center=cost(V,x_center);
        do{ 
            x_left = max(x_min, x_center - Dx);
            x_right = min(x_max, x_center + Dx);
            y_left = cost(V,x_left);
            y_right = cost(V,x_right);
            //choose the center as the point of minimum cost
            if (y_left < min(y_center, y_right)) {
                x_center = x_left;
                y_center = y_left;
                }
            else if  (y_right < min(y_center, y_left)) {
                x_center = x_right;
                y_center = y_right;
                }
            Dx = Dx/2;
        }while( Dx>0 );
        cout << y_center;
    }
    else if (METHOD==2){
        sort(V.begin(),V.end());
        x = V[n/2];//Does not matter in case 'n' is even which will be picked as median
        cout << cost(V,x);
    }        
}