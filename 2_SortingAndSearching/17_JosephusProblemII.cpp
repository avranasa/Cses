#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

typedef tree<int,null_type,less<int>,rb_tree_tag, tree_order_statistics_node_update> indexed_set;
//https://codeforces.com/blog/entry/11080
//https://github.com/mrsac7/CSES-Solutions/blob/master/src/2163%20-%20Josephus%20Problem%20II.cpp
 
 
int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int n,k, pos=0;
    cin >> n >> k;
    indexed_set S;
    indexed_set ::iterator pos_set;
    for (int i=1;i<=n;i++) {
        S.insert(i);
    }
 
    while (!S.empty()){
        pos = (pos+k)%S.size();
        pos_set = S.find_by_order(pos);        
        cout << *pos_set <<" ";
        S.erase(pos_set);//this is slow!!! 
    }    
}



/*even though it is correct it is slow... I think it is n*log(n) 
int main(){
    int n,k, pos=0;
    cin >> n >> k;
    set <int> S;
    set <int> ::iterator pos_set = S.begin();
    for (int i=1;i<=n;i++) {
        S.insert(pos_set,i);
        pos_set ++;
    }

    while (!S.empty()){
        pos = (pos+k)%S.size();
        pos_set = S.begin();        
        advance(pos_set,pos);//this is slow!!! 
        cout << *pos_set <<" ";
        S.erase(pos_set);//this is slow!!! 
    }    
}*/