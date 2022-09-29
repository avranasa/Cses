#include <bits/stdc++.h>
using namespace std;

pair <int,int> find_hotels(vector<int>& H, vector<int>& nextH, int r, int p){
    //returns (i,j) where j-th is the hotel with equal or more than r rooms and 
    //j is the previous hotel checked that was pointing to the j-th hotel
    // returns (-1,-1) if no hotel was found
    //p is the previous hotel checked
    int next_p = nextH[p];
    if ((next_p < 0) || (next_p>=int(H.size()))) return make_pair(-1,-1);
    if (H[next_p]>=r) return make_pair(next_p, p);
    return find_hotels(H, nextH, r, next_p);
}


void point_to_next_hotel(vector<int>& H, vector<int>& nextH, int i, int p){
    //Updates nextH
    //point i-th hotel to the j-th one (i<j) but j with more available rooms
    //Function is called recursively and in each iteration it checks the p-th hotel
    
    if (H[p]>H[i]){//success, no more jumping needed
        nextH[i]=p;
        return;
    }
    if ((p==int(H.size()-1))||(nextH[p]==-1)) {
        //failure and no further search is needed
        nextH[i] = -1;
        return;
    }
    if (nextH[p] == -2)       
        point_to_next_hotel(H, nextH, i, p+1); 
    else 
        point_to_next_hotel(H, nextH, i, nextH[p]);   

}

int main(){
    int n, m, h, r, h_prev;
    cin >> n >> m;
    vector <int> H, nextH;//nextH: for each hotel which next hotel has more free rooms. 
                          //      -1 if there is no next hotel with more free rooms 
                          //      -2 if not yet defined the next hotel
                        
    for (int i=0; i<n; i++){
        cin >> h;
        H.push_back(h); nextH.push_back(-2);
    }
    vector <int> idx(n);
    iota(idx.begin(), idx.end(),0);
    stable_sort(idx.begin(),idx.end(), [&H](int i, int j){return H[i]<H[j];});

    for (int x:idx) cout << x <<"  ";
    cout << endl;


    for (int i : idx)  point_to_next_hotel(H, nextH, i, i); // this step is slow... Maybe you could think of 
                            // using a min range to find in the range of idx (starting from the 'current' index till the end)
                            // the minimum idx value. This value will be the next hotel to be check from the current hotel
                            // Then you update the value of the chosen next hotel in the idx to n+1 so as not to be chosen again
                            // (or if chosen you will see that you chose the n+1 hotel so you know it does not exist...)...

    for(int j=0; j<m; j++){
        cin >> r;
        if (H[0]>=r) h=0;
        else tie(h, h_prev) = find_hotels(H, nextH, r, 0);
        cout << h+1 << " " ;//<< h_prev+1 << endl;        
        if (h==-1) continue;
        H[h] -= r; nextH[h]=-2; //reduce rooms
        point_to_next_hotel(H, nextH, h, h);//correcting nextH[h]  
        if (h>0) point_to_next_hotel(H, nextH, h_prev, h);//correcting nextH[h_prev]
    }
}