#include <iostream>
#include <vector>
#include <set>
using namespace std;


int NroundsAssociatedWith_v1_v2(int v1,int v2, vector <int> & Ind){
    int v_min, ans=0, n=Ind.size();
    if (abs(v1-v2)>1){
            for (auto v:{v1,v2}){
                if ((v>1) && (Ind[v-2]>Ind[v-1])) ans++;
                if ((v<n) && (Ind[v-1]>Ind[v])) ans++;
            }
        }
        else{
            v_min = min(v1,v2);
            if ((v_min>1) && (Ind[v_min-2]>Ind[v_min-1])) ans++;
            if (Ind[v_min-1]>Ind[v_min]) ans ++;
            if ((v_min+1<n) && (Ind[v_min]>Ind[v_min+1])) ans++;
        }
    return ans;
}

int main(){
    int n,M,x, N_rounds=1, i1, i2, i1_prev, i2_prev, v1, v2;
    cin >> n >> M;
    vector <int> Ind(n), X(n); 
    for (int i=0; i<n; i++){
        cin >> x;
        Ind[x-1] = i;
        X[i] = x;
    }
    for (int p=1; p<n; p++) if (Ind[p-1]>Ind[p]) N_rounds ++;
    for (int m=0;m<M;m++){
        cin >> i1 >> i2;
        i1 --; 
        i2 --;
        v1 = X[i1]; 
        v2 = X[i2];
        N_rounds -= NroundsAssociatedWith_v1_v2(v1, v2, Ind);
        
        X[i1] = v2; 
        X[i2] = v1;
        Ind[v1-1] = i2; 
        Ind[v2-1] = i1;
        N_rounds += NroundsAssociatedWith_v1_v2(v1, v2, Ind);
        cout << N_rounds<<endl;
    }
}

