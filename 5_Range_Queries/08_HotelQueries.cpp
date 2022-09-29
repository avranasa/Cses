#include <bits/stdc++.h>
using namespace std;

int max_query(int a, int b, vector <int> & MaxSegTree){
    int n = MaxSegTree.size()/2, ans=-1;
    a += n; b += n;    
    while( a<=b ){
        if (a%2 == 1) ans = max(ans,MaxSegTree[a++]);
        if (b%2 == 0) ans = max(ans,MaxSegTree[b--]);
        a /= 2; b /= 2;
    }
    return ans;
}


void add_rooms(int h, int r, vector <int> & MaxSegTree){
    h +=  MaxSegTree.size()/2;
    MaxSegTree[h] += r;
    for (h /=2; h >= 1; h/=2){
        MaxSegTree[h] = max(MaxSegTree[2*h],MaxSegTree[2*h+1]);
    }
}

int find_hotel(int r, vector <int> & MaxSegTree){
    int h = 0, n = MaxSegTree.size()/2 ; 
    if (MaxSegTree[h+n]>=r) return 0; //checking if the first hotel is fine

    //finding the hotel before the one we search
    for (int b= n/2; b>=1; b/=2){
        while ( h+b<n && max_query(0, h+b, MaxSegTree)<r) h+=b;
    }
    h++; // the hotel we search
    if (h==n) return -1;//no hotel is good
    else return h;
}


int main(){
    int n, m, h, r;
    cin >> n >> m;
    vector <int> MaxSegTree(2*n,0);
    for (int i=0; i<n; i++){
        cin >> h;
        add_rooms(i, h, MaxSegTree);
    } 
    for (int i=0; i<m; i++){
        cin >> r;
        h = find_hotel(r, MaxSegTree);
        cout << h+1 <<" ";
        if (h>=0) add_rooms(h, -r, MaxSegTree);        
    }

}