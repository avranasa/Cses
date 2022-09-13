#include <bits/stdc++.h>
#define ll long long
#define  N 1000000007
using namespace std;


void MoreComb(vector<ll> & Comb, vector<ll> & New_comb, ll x_prev_min, ll x_prev_max, ll x_min, ll x_max){
    ll val;
    for(ll x=x_min; x<=x_max; x++){
        val = 0;
        if (x-1 >= x_prev_min) val += Comb[x-x_prev_min-1];
        if (x>=x_prev_min && x<=x_prev_max) val += Comb[x-x_prev_min];
        if (x+1<=x_prev_max) val += Comb[x-x_prev_min+1];
        New_comb.push_back(val%N);
    }
}

ll max(ll a, ll b){
    if (a>b) return a;
    else return b;
}
ll min(ll a, ll b){
    if (a>b) return b;
    else return a;
}


int main(){
    ll n, m, x, x_prev_min, x_prev_max, x_min, x_max, add, x_prev=-1, x_temp, ans, total_ans=1;

    cin >> n >> m;
    vector <ll> Xmin;
    vector <ll> Xmax;
    for (ll i=0; i<n; i++){
        cin >> x;
        if (x==0){
            if (x_prev!=0){
                Xmin.clear();
                Xmax.clear();
                if (i!=0){
                    Xmin.push_back(x_prev);
                    Xmax.push_back(x_prev);
                }
            }
            if (x_prev!=-1){
                Xmin.push_back(max( Xmin.back()-1, 1));
                Xmax.push_back(min( Xmax.back()+1, m));
            }
            else{
                Xmin.push_back(1);
                Xmax.push_back(m);
            }
        }
        
        
        if ((x!=0 && x_prev==0) || (i==n-1 && x==0)){
            
            //Need to update total_ans
            if (i!=n-1 || x!=0){
                if ((Xmax.back()+2<x) || (Xmin.back()-2>x)) {
                    cout << 0 ; //Impossible ... no way    
                    return 0;
                }
                x_temp=x;
                for(auto it=Xmin.rbegin(); it!=Xmin.rend(); it++){
                    x_temp--;*it = max(x_temp,*it);               
                }
                x_temp=x;
                for(auto it=Xmax.rbegin(); it!=Xmax.rend(); it++){
                    x_temp++;*it = min(x_temp,*it);    
                }
            }

            ll  size_Comb=1, size_New_Comb;
            vector <ll> Comb, New_Comb;
            for(int i = Xmin[0];i<=Xmax[0];i++)  Comb.push_back(1);

            for (ll i=1; i<Xmin.size(); i++) {
                x_prev_min = Xmin[i-1];
                x_prev_max = Xmax[i-1];
                x_max = Xmax[i];
                x_min = Xmin[i]; 
                //cin >> add;
                MoreComb(Comb, New_Comb, x_prev_min, x_prev_max, x_min, x_max);
                Comb.swap(New_Comb);  
                New_Comb.clear();
                //cout <<endl;
                //for (auto elem:Comb) cout<< elem <<" ";
            }
            ans=0;
            for(auto elem:Comb) {
                ans += elem;
                ans %= N;
            }
            if (total_ans==0) total_ans = ans;
            else total_ans = (total_ans*ans)%N;
            //cout <<endl << "ans is " << i+1<<" here: "<< total_ans;
            //cout<< "yolo";
        }
        if ((i>0)&& (x>0) && (x_prev>0) && (abs(x-x_prev)>1)) {
            cout << 0 ; //Impossible ... no way    
            return 0;
        }
        x_prev = x;
    }

    cout << total_ans;
}