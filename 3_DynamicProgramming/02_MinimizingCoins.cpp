#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <cassert>
#include <vector>
using namespace std;

/*CHECK THE FOLLOWING ALGORITHM
For every round:
    For every sum that was discovered JUST IN THE PREVIOUS round
        Discover if you can reach new sums by trying all the coins
            if you cannot cout "-1"
*/


int main(){
    int n, x, c, N_rounds=0;
    cin >> n >> x;
    int Coins[n];
    bool SumFound[x+1]={};  
    vector <int> PreviousSums, NewSums;
    SumFound[0] = true;//the 0 sum.
    PreviousSums.push_back(0);
    for (int i=0; i<n; i++){
        cin >> c;
        Coins[i]=c;
    }
    while (true)  {
        N_rounds ++;
        for (auto c:Coins){
            for(auto s:PreviousSums){
                if (s+c>x) continue;
                if (!SumFound[s+c]){
                    SumFound[s+c] = true;
                    NewSums.push_back(s+c);
                }
                if (s+c==x){
                    cout<< N_rounds;
                    return 0;
                }
            }
        }
        if (NewSums.empty()){
            cout << "-1";
            return 0;
        }
        PreviousSums.clear();
        PreviousSums.swap(NewSums);
    }   
}



//============================================


/*This code to work fast it assumes that when 
it is impossible to reach the sum x (i.e. have to
print "-1") then the number of coins and x are small*/

//The algorithm tries to find a fast solution and then
//only considers faster solutions.
/*
int main(){
    int n, x, c, N_rounds=-1;
    cin >> n >> x;
    int Coins[n], NcoinsPerSum[x+1]={};
    vector <int> Sums, NewSums;
    for (int i=0; i<n; i++){
        cin >> c;
        Coins[i]=c;
    }
    sort(Coins, Coins+n, greater<>());
    Sums.push_back(0);
    

    int s_prev;
    for (auto c: Coins){
        for(auto s : Sums){

            //The below is WRONG because you do not know if NcoinsPerSum[s] is actually the minimum. 
            //if ((N_rounds>0) && ( (s + (N_rounds-NcoinsPerSum[s]+1)*c) < x) ) break;//All the rest sums will be smaller and also all the rest coins so there is no way it can reach x the sum
                                                                                //using smaller coins and less than N_rounds

            //CHECK
            if ((N_rounds>0) && ( s+(N_rounds- s/Coins[0] )*c< x) ) break; //To reach s you need at least s/Coins[0] coins since the max coin is Coins[0]

            int s_temp = s+c;
            while (s_temp<=x) {
                if  (NcoinsPerSum[s_temp]==0){
                    NcoinsPerSum[s_temp] = NcoinsPerSum[s_temp-c]+1;
                    NewSums.push_back(s_temp);
                }
                else NcoinsPerSum[s_temp] = min(NcoinsPerSum[s_temp],  NcoinsPerSum[s_temp-c]+1);
                if (s_temp == x) N_rounds = NcoinsPerSum[x]; 
                s_temp+=c;
            }      
        }
        if (NewSums.size()>0){
            for (auto s:NewSums) Sums.push_back(s);
            NewSums.clear();
            sort(Sums.begin(), Sums.end(), greater<>());
        }
    }    
    cout <<N_rounds;
    return 0;    
}

*/