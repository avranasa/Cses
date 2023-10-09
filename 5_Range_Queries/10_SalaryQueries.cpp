//1st way: use  tree_order_statistics_node_update. Create a ordered-multiset that will contain the 
//salaries. Using order_of_key(p) you can find how many employees get less money. And also I think
//you can delete one salary p_old and insert the updated one p_new.


//A second way is first to read all the queries and save all the possible salaries. If they are N
//the possible values then sort them and create an integer array of N elements that will contain
//the number of employees with that salary. A bit ugly this solution since you look all the queries
//and you do not process them one by one.

#include <bits/stdc++.h>
#define ff first
#define ss second
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
using namespace std;
const int md = 1000000007;

int sum(int a, int b, int n, int tree[]){
    a+=n; b+=n;
    int s=0;
    while (a<=b) {
        if (a%2==1) s+=tree[a++];
        if (b%2==0) s+=tree[b--];
        a/=2; b/=2;
    }
    return s;    
}

void add(int k, int x, int n, int tree[]){
    k += n;
    tree[k] += x;
    for (k/=2; k>=1; k/=2) tree[k]+=x;
}

int main(){    
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    int n,q,s,x, pos1, pos2;
    char c;
    cin >> n >> q;
    vector<int> Sal, Sal_init, Sal_all;
    vector<tuple<int,int,int>> Q;
    for(int i=0; i<n; i++){
        cin >> s;
        Sal.push_back(s);//for every employee it keeps tracks its salary
        Sal_all.push_back(s);  
    }
    for(int i=0; i<q; i++){
        cin >> c >> s >> x;
        if (c=='?') Q.push_back({1,s,x});
        else {
            Q.push_back({2,s,x});
            Sal_all.push_back(x);
        }
    }
    sort(Sal_all.begin(),Sal_all.end());
    auto it = unique(Sal_all.begin(), Sal_all.end());
    Sal_all.erase(it, Sal_all.end());
    n=Sal_all.size();
    int tree[2*n]={0}, i1=0;
    for(auto s:Sal){
        pos1 = lower_bound(Sal_all.begin(),Sal_all.end(),s)-Sal_all.begin();
        add(pos1,1,n,tree);
        i1++;  
    }
    for(auto const&[type_q, x1,x2]: Q){
        if (type_q==1){
            pos1 = lower_bound(Sal_all.begin(),Sal_all.end(),x1)-Sal_all.begin();
            pos2 = upper_bound(Sal_all.begin(),Sal_all.end(),x2)-Sal_all.begin() - 1;
            cout << sum(pos1, pos2, n, tree) _endl;
        }
        else{
            pos1 = lower_bound(Sal_all.begin(),Sal_all.end(),Sal[x1-1])-Sal_all.begin();            
            add(pos1, -1, n, tree);
            Sal[x1-1] = x2;
            pos1 = lower_bound(Sal_all.begin(),Sal_all.end(),Sal[x1-1])-Sal_all.begin();                         
            add(pos1, 1, n, tree); 
        }
    }    

}
