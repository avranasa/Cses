#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
#define int long long
using namespace std;
const int md = 1000000007;

signed main(){
    ios::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);
    int n, x, y, x0, y0, curr_p, p;
    unsigned int ans=8e18, dx, dy_min, dy; 
    vector<int> X, Y;
    cin >> n;
    for (int i=0; i<n; i++){
        cin >> x >> y;
        X.push_back(x);
        Y.push_back(y);
    }
    vector<size_t> I_x(n), I_y(n);//I_x[i] gives you the i-th biggest x. Same for I_y[i]
    vector<size_t> R_y(n); //R_y[i] shows what is the rank of Y[i]
    iota(I_x.begin(),I_x.end(),0);
    iota(I_y.begin(),I_y.end(),0);
    stable_sort(I_x.begin(), I_x.end(), [&X](size_t i1, size_t i2) {  return X[i1] < X[i2]; });
    stable_sort(I_y.begin(), I_y.end(), [&Y](size_t i1, size_t i2) {  return Y[i1] < Y[i2]; });
    for (int i=0; i<n; i++) R_y[I_y[i]] = i;

    
    int N_y = 2; //A hyperparameter. Checks on first N_y points that are
        //closest on the y-dimensions from each side to the "current" point.
        //Helps breaking faster the "investigation" of each point. (faster seems to be N_y=1)
        //Whatever value N_y>=1 has the dy_min will be the same. The only way it might 
        //help is maybe finding faster with this heuristic a smaller total min. distance (i.e. "ans") 
    for (int i=0; i<n-1; i++){
        //checking thei i-th point with all the j-th points (j>i) to see if we can
        //find a smaller than the already smaller found distance "ans". If found then 
        //"ans" is updated.
        curr_p = I_x[i];
        x0=X[curr_p];
        y0=Y[curr_p];
        dy_min = 4e18;
        for (int r=-N_y; r<=N_y; r++){            
            p = R_y[curr_p]+r;
            if ((r==0)||(p<0)||(p>=n)) continue;
            x=X[I_y[p]];
            y=Y[I_y[p]];
            dy = (y-y0)*(y-y0);
            dy_min = min<unsigned int>(dy_min, dy);            
            ans = min<int>(ans, (x-x0)*(x-x0)+dy);//Updating "ans" in case we found a smaller total min. distance
        }
        for(int j=i+1; j<n; j++){
            x=X[I_x[j]];
            y=Y[I_x[j]];
            dx = (x-x0)*(x-x0);
            if (ans<=dx + dy_min) break;//all next points will have for sure bigger dx and dy_min and so
                                        // bigger distance  than "ans" from the "curr_p" point
            ans = min<int>(ans, dx + (y-y0)*(y-y0) );
        }
    }
    cout << ans;
}
 /*
 //This is another solution found on github by Author: Sachin Srivastava
 //not faster but seems quite clean

#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define P pair<int, int>
#define X first
#define Y second

int norm(P a, P b) {return (b.X - a.X) * (b.X - a.X) + (b.Y - a.Y) * (b.Y - a.Y);}

signed main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int n; cin>>n;
    vector<P> v(n);
    int d = LLONG_MAX;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        v[i] = {x, y};
    }
    sort(v.begin(), v.end());
    set<P> s = {{v[0].Y, v[0].X}};//This set will contain only points P with P.X smaller than v[i].X
                    //assuming that v[i] is the point we check at iteration i. Also it has only points P
                    //that v[i].X-P.X < dd, where dd is the smallest found distance. 
    int j = 0;
    for (int i = 1; i < n; i++) {
        int dd = ceil(sqrt(d));
        while (j < i && v[j].X < v[i].X - dd) {
            s.erase({v[j].Y, v[j].X});
            j++;
        }

        auto l = s.lower_bound({v[i].Y - dd, 0});
        auto r = s.upper_bound({v[i].Y + dd, 0});
        for (auto it = l; it != r; it++) {
            d = min(d, norm({it->Y, it->X}, v[i]));
        } 
        s.insert({v[i].Y, v[i].X});
    }
    cout << d;
}
*/
