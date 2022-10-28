#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, a, b, Method = 2; //Method 1 is slightly faster
    cin >> n ;
    int Alloc[n], max_k=0;
    queue <int> Empty_rooms;
    if (Method == 1){    
        vector <int> A, B, idx_A, idx_B;
        for (int i=0; i<n; i++){
            cin >> a >> b;
            A.push_back(a);
            B.push_back(b);
            idx_A.push_back(i);        
            idx_B.push_back(i);
        }
        A.push_back(2e9);idx_A.push_back(n); //Avoid side effects. Last (fake) arrival is after everyone else left.
        stable_sort(idx_A.begin(),idx_A.end(), [&A](int i1, int i2){return A[i1]<A[i2];}); 
        stable_sort(idx_B.begin(),idx_B.end(), [&B](int i1, int i2){return B[i1]<B[i2];});
        int i_A=0, i_B=0, t_A, t_B, id_A=idx_A[0], id_B=idx_B[0];
        for (int i =0; i<2*n; i++){
            t_A = A[id_A];
            t_B = B[id_B];
            if (t_A <= t_B){ //new arrival
                if (Empty_rooms.empty()) Alloc[id_A] = ++max_k;//new room needed
                else {
                    Alloc[id_A] = Empty_rooms.front();
                    Empty_rooms.pop();
                }
                id_A = idx_A[++i_A];
            }
            else{
                Empty_rooms.push(Alloc[id_B]);
                id_B = idx_B[++i_B];
            }
        }

    }
    else if (Method == 2){
        priority_queue <tuple<int, bool, int>> Q; //maximum pops first!
        int t, id; 
        bool arrival;
        for (int i=0;i<n;i++){
            cin >> a >> b;
            Q.push({-a,true,i});//false > true, i.e. the arrivals will be treated first in case at the same time there is also a departure
            Q.push({-b,false,i});
        }
        while (!Q.empty()){
            tie(t, arrival, id)= Q.top();Q.pop();
            if (arrival){
                if (Empty_rooms.empty()) Alloc[id] = ++max_k;
                else{ Alloc[id] = Empty_rooms.front();  Empty_rooms.pop();}
            } 
            else Empty_rooms.push(Alloc[id]);
        }
    }
    
    cout << max_k << endl;
    for(int i=0; i<n; i++) cout << Alloc[i] << " ";    

}