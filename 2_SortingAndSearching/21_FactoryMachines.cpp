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
    //O(N_mach)
    int N_prod = 0;
    for(auto t : T_mach) N_prod+= t_total/t;
    return N_prod;
}



signed main(){
    int  METHOD = 1;
    int N_mach, N_prod, k, t_min=0, i_mach, t_mach_min=inf;
    cin >> N_mach >> N_prod;
    vector <int> T_mach;//time each machine needs for each product
    for (int i=0;i<N_mach;i++){
        cin >> k;
        T_mach.push_back(k); 
        if (k<t_mach_min) t_mach_min=k;
    }

    if (METHOD == 1){        
        int init_method = 2, N_prod_init = 0, t_init_approx, n_prod_unit, t_min_unit;   
        priority_queue <pair<int,int>> T; //<additional time for a machine to do another product, id of the machine>
        if (init_method == 1){
            // Will work in O(N_prod*log(N_mach)) but is too slow for the problem's constraints. SLOW   
            for (int i=0;i<N_mach;i++) T.push({-T_mach[i],i});
        }
        else if (init_method == 2){
            // Will work in O( (N_prod-N_prod_init)*log(N_mach) ) time, which I think it is equal to 
            // O( (N_prod%N_mach)*log(N_mach) ) which is equal to O( N_mach*log(N_mach) )
            double n_prod_per_t_mach_min = 0.0;
            for(auto t:T_mach) n_prod_per_t_mach_min += t_mach_min / (double)t;
            t_init_approx = (int)(N_prod/n_prod_per_t_mach_min*t_mach_min);
            for (int i=0;i<N_mach;i++){
                n_prod_unit = t_init_approx/T_mach[i];
                t_min_unit = n_prod_unit*T_mach[i];
                N_prod_init += n_prod_unit;
                if (t_min<t_min_unit) t_min=t_min_unit;//useful if N_prod_init==N_prod
                T.push({-t_min_unit-T_mach[i],i});
            }
        }    
        for(int i=N_prod_init; i<N_prod; i++){
            t_min = -T.top().first; 
            i_mach = T.top().second;
            T.pop();
            T.push({-t_min-T_mach[i_mach],i_mach});
        }
        cout << t_min;
    }
    else if (METHOD == 2){
        //In i-th iteration it tries to improve the estimation of the needed time  by a margin T_mach[i]        
        //Works in O(N_mach*log(N_prod)+log(N_mach)*N_mach)... Faster
        sort(T_mach.begin(), T_mach.end());
        int n_lower=0, n_upper=N_prod, N_prod_new; 
        while(n_lower < n_upper-1){
            //n_lower is infeasible and n_upper is feasible solution
            k=(n_upper+n_lower)/2;//always holds that n_lower < k < n_upper
            N_prod_new = Max_num_products(T_mach,k*T_mach[0]) ;
            if (N_prod_new>= N_prod) n_upper = k;
            else  n_lower = k;
        }
        assert((n_upper-n_lower==1) && "went wrong");
        int t_lower=n_lower*T_mach[0], t_upper=n_upper*T_mach[0], t_c, k;
        vector <int> T_candidate ;
        for (int i=1; i<N_mach; i++){
            t_c = (t_upper/T_mach[i])*T_mach[i];
            if ((t_c>t_lower) && (t_c<t_upper)) T_candidate.push_back( t_c );
        }
        sort(T_candidate.begin(),T_candidate.end());
        T_candidate.push_back(t_upper);
        int i1=0, i2=T_candidate.size()-1;
        while (i1<i2){
            //i2 is always representing a feasible already known solution
            //i1 is representing an unknown solution which maybe feasible or not
            k = (i1+i2)/2;//k<i2
            t_c = T_candidate[k];
            N_prod_new = Max_num_products(T_mach,t_c) ;
            if (N_prod_new >= N_prod) {
                t_upper = t_c;
                i2 = k;
            }
            else {
                t_lower = t_c;
                i1 = k+1;
            }
        }
        cout << t_upper;           
    }
    else if (METHOD == 3){
        // Binary search until you find the minimum time. Depends on the fact that the solution must be integer        
        //Works in O( log(N_prod*min(T_match)) )
        int t_lower=0, t_upper = N_prod*t_mach_min, t_c, N_prod_new;
        while(t_lower<t_upper-1){
            t_c = (t_lower+t_upper)/2;
            N_prod_new = Max_num_products(T_mach,t_c) ;
            if (N_prod_new >= N_prod) t_upper = t_c;
            else t_lower = t_c;
        }
        cout << t_upper;           
    }
}