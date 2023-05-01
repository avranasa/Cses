//Stupid assumption that the problem does are that if a, b employes are given
//then it may be that a==b and then the response is a. Also if a is boss of b 
//then again the response is a.
#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '  
#define _space_ <<' '<<
using namespace std;

int H[18][200000];

int FindBoss(int e, int h, int & n){
    //finds given hierarchy matrix H the 'h' times superior of employer e. -1 if it does not exists
    int pos = 0;
    if (h>=n) return -1;
    while(h>0){
        if (h%2==1) e=H[pos][e];
        if (e==-1) break;
        h/=2; pos++;
    }
    return e;
}


void rank_e(int rank[], vector<int> H_inv[], int e, int r){
    rank[e] = r;//the smaller the rank the higher in hierarchy
    for(auto e_new: H_inv[e]) rank_e(rank, H_inv, e_new, r+1);
}


int main(){
    ios_base::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);    
    int WAY = 2;
    int n, q, b, mid_b, a, boss_a, boss_b, boss_ans, diff_r,h_max,h_min, h_mean;
    cin >> n >> q;
    int rank[n];//H[pos][i] stores for employee i the 2^pos times superior
    vector<int> H_inv[n];//H_inv[i] for boss i it stores all its direct "inferiors"    
    H[0][0] = -1;
    for (int i=1; i<n; i++){
        cin >> b;
        H[0][i] = b-1;
        H_inv[b-1].push_back(i);
    }
    //Rank the employees.
    rank_e(rank, H_inv, 0, 0);

    //building the hierarchy table of powers of 2... i.e. for each employee who is the 2**pos higher boss. 
    for(int pos=1; (1<<pos)<n; pos++){        
        for(int i=0; i<n; i++){
            mid_b = H[pos-1][i];
            H[pos][i] = (mid_b==-1) ? -1 : H[pos-1][mid_b];
        }
    }
    
    
    //Answers
    for(int i=0; i<q; i++){
        cin >> a >> b; 
        a--; b--;
        if (rank[a]>rank[b]) swap(a,b);//assume/assert that employee a is higher ranked.
        diff_r = rank[b]-rank[a];
        b = FindBoss(b, diff_r, n); diff_r = 0; //not necessary for WAY 1 but speeds up from 0.92 -> 0.6 !
                                                //obligatory for WAY 2

        if (a==b) {cout << a+1 _endl; continue;}//not necessary for WAY 1 but speeds up a bit. Obligatory for WAY 2
        if ((a==0) || (b==0)){cout << 1 _endl; continue;}//not necessary for WAY 1 but speeds up a bit. Obligatory for WAY 2
        
        
        if (WAY==1){    //BINARY SEARCH 
            h_max = rank[a];//represents always a valid solution (starting by pointing to the boss of all)
            boss_ans = 0;
            h_min = 0;
            while(h_max>=h_min){
                h_mean = (h_max+h_min)/2;
                boss_a = FindBoss(a, h_mean, n);  
                boss_b = FindBoss(b, h_mean+diff_r, n);
                if (boss_a!=boss_b) h_min = h_mean+1;
                else {
                    h_max = h_mean;
                    boss_ans = boss_a;
                    if (h_max==h_min) break;
                }            
            }
            cout << boss_ans+1 _endl;
        }
        else if (WAY==2){ //SEARCHING IN POWERS OF 2.
            // Much faster than WAY 1. (0.6 -> 0.3, i.e. twice faster)
            int pos;
            while(H[0][a]!=H[0][b]){
                //going up the hierarchy in powers of 2. here another binary search could be done to find
                //the pos even faster but since there are only 18 possible values it is not that necessary.
                for(pos=0; pos<18; pos++) if (H[pos+1][a]==H[pos+1][b]) break;
                a = H[pos][a];
                b = H[pos][b];
            }
            cout << H[0][a]+1 _endl;
        }    
    }
}