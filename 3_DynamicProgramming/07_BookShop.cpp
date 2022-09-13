#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main(){
    int n , X, s, h;
    cin >> n >> X;
    vector <int> Prices, Pages;
    for (int i=0; i<n; i++){
        cin >> h;
        Prices.push_back(h);
    }
    for (int i=0;i<n; i++){
        cin >> s;
        Pages.push_back(s);
    }


    int MaxPages[X+1] = {};
    for (int b=0; b<n; b++){
        h = Prices[b];
        s = Pages[b];
        //cout <<sizeof(MaxPages)/sizeof(*MaxPages) << " - ";
        for(int x=X; x>=h; x--){//From the highest to the lowest price to assure you do not use one book twice
            MaxPages[x] = max(MaxPages[x],MaxPages[x-h]+s);
        }
        //cout <<sizeof(MaxPages)/sizeof(*MaxPages)<< endl;
    }

    //cout << endl;
    cout<<MaxPages[X];

}