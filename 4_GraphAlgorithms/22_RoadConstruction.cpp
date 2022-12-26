#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
//#define int long long
using namespace std;
const long long inf = 1LL<<60; //1.5e18, max(long long)= 9e18 = 2^63
const int md = 1000000007;

/*NOTES
vector x = vector y
the content of y will be copied to x

    vector <vector <int> *> Comp;//for each city it shows the component the city belongs
    for(int i=0; i<n; i++) {
        Comp.push_back(new vector<int>);
        Comp[i]->push_back(i);

    }
    F(Comp, n);
    Comp[0]->push_back(10);
    Comp[1] = Comp[0];
    F(Comp,n);
    Comp[1]->at(0) = 32;
    F(Comp, n);


void F(vector<vector<int> *> C, int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<C[i]->size(); j++) cout<< 1+ C[i]->at(j) _space;
        cout<< "   "<< C[i];
        cout _endl;
    }
    cout _endl;
    cout _endl;

    
}
*/
signed main(){
    ios::sync_with_stdio(0);    
    cin.tie(0);  cout.tie(0);    
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int Version = 2;
    int n, m, a, b; 
    cin >> n >> m;
    int max_s=1, n_comp=n;


    //Version 1
    if (Version == 1){
        //The following solution is slow both due to the multiple (unnecessary) insertions and updates
        //Nonetheless I am almost sure that the complexity is O(n*logn) so I do not see why it takes 
        //more than 45sec in the biggest problems of cses.fi instead of less than 0.1sec...

        vector <vector <int> *> Comp;//for each city it shows the component the city belongs
        for(int i=0; i<n; i++) {
            Comp.push_back(new vector<int>);
            Comp[i]->push_back(i);
        }
        for(int i=0; i<m; i++){
            cin >> a >> b;
            a--;b--;
            if (Comp[a] != Comp[b]){
                if (Comp[a]->size()<Comp[b]->size()) swap(a,b);     
                Comp[a]->insert(Comp[a]->end(), Comp[b]->begin(), Comp[b]->end()); //multiple insertions
                //for(auto p: *Comp[b]) Comp[a]->push_back(p); //same as line below (also in terms of speed)
                for(int j=0; j<Comp[b]->size(); j++) Comp[Comp[b]->at(j)] = Comp[a]; //multiple updates   
                max_s = max(int(Comp[a]->size()), max_s);
                n_comp --;       
            }
            cout << n_comp _space_ max_s _endl; 
        }
    }
    else if (Version == 2){
        //Here I do not do the multiple unnessary insertions and updates. In this version you lose the ability given one 
        //component to immediately give all of the nodes belonging to it (even though it is not needed in the problem 
        //that is why insertions & updates are unnecessary).

        vector <pair<int, int>> Comp;//for each city it shows the component the city belongs and the size of the component
        for(int i=0; i<n; i++) {
            Comp.push_back({i,1});
        }
        for(int i=0; i<m; i++){
            cin >> a >> b;
            a--;b--;
            while(a != Comp[a].first) a = Comp[a].first;            
            while(b != Comp[b].first) b = Comp[b].first;
            if (a != b){
                if (Comp[a].second<Comp[b].second) swap(a,b);   
                Comp[a].second += Comp[b].second;
                Comp[b].first = a;       
                max_s = max(Comp[a].second, max_s);
                n_comp --;       
            }
            cout << n_comp _space_ max_s _endl; 
        }

    }
        

}