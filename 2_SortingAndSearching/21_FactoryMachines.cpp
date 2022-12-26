//Binary search to find the number of products the cheaper can make
//and then binary reach for the specific time
#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
#define int long long
using namespace std;
const long long inf = 1LL<<60; //1.5e18, max(long long)= 9e18 = 2^63
const int md = 1000000007;

int Max_num_products(vector <int> & T_mach, int t_total){
    //Returns the maximum number of products produced in t_min
    int N_prod = 0;
    for(auto t : T_mach) N_prod+= t_total/t;
    return N_prod;
}

pair<int,int> Tighten_Bound(vector <int> & T_mach, int t_lower, int t_upper, int i_mach, int N_prod){
    //t_lower is a lower bound on the minimum time needed (provides a non-feasible/achievable solution)
    //t_upper is the upper bound. 
    //The function tries to tighten the bounds by looking greedily the best solution for the 
    //i_mach machine
    int t_mach = T_mach[i_mach], k, n_lower = t_lower/t_mach, n_upper = t_upper/t_mach;//n_upper*t_match<=t_upper
    int t_upper_new = n_upper*t_mach;
    if ( t_upper_new < t_lower) return {t_lower, t_upper};
    if (( t_upper_new < t_upper) && (Max_num_products(T_mach, t_upper_new) < N_prod))  return {t_lower, t_upper};
    //t_upper_new is a feasible solution and equal or better upper bound than previous one

    while(n_lower < n_upper-1){
        k=(n_upper+n_lower)/2;//always k<n_upper
        if (Max_num_products(T_mach,k*t_mach) >= N_prod) n_upper = k;
        else  n_lower = k;
    }
    return {n_lower*t_mach, n_upper*t_mach};
}


signed main(){
    int N_mach, N_prod, k, t_min=0, i_mach, METHOD = 2;
    cin >> N_mach >> N_prod;
    vector <int> T_mach;//time each machine needs for each product
    priority_queue <pair<int,int>> T; //<additional time for a machine to do another product, id of the machine>
    for (int i=0;i<N_mach;i++){
        cin >> k;
        T_mach.push_back(k); 
    }

    if (METHOD == 1){
        //Works in N_prod*log(N_mach) but is too slow for the problem's constraints. SLOW
        for (int i=0;i<N_mach;i++) T.push({-T_mach[i],i});
        for(int i=0; i<N_prod; i++){
            t_min = -T.top().first; 
            i_mach = T.top().second;
            T.pop();
            T.push({-t_min-T_mach[i_mach],i_mach});
        }
        cout << t_min;
    }
    else if (METHOD == 2){
        //Works in N_mach*log(N_prod)... Faster
        sort(T_mach.begin(), T_mach.end());
        int t_lower=T_mach[0], t_upper = T_mach[0]*N_prod;
        for (int i=0; i<N_mach; i++)
            tie(t_lower,t_upper) = Tighten_Bound( T_mach, t_lower, t_upper, i, N_prod);
        cout << t_upper;   
    }
}