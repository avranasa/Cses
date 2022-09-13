#include <iostream>
using namespace std;

int main(){
    pair <long long, long long> p1, p2,p3 , v1,v2;
    int x,y, n;
    cin >>n;
    for (int i=0;i<n;i++){
        cin >> p1.first >> p1.second;
        cin >> p2.first >> p2.second;
        cin >> p3.first >> p3.second;
        v1.first = p2.first-p1.first;
        v2.first = p3.first-p1.first;
        v1.second = p2.second-p1.second;
        v2.second = p3.second-p1.second;
        long long sinT = v1.first*v2.second - v2.first*v1.second;
        if (sinT==0) cout <<"TOUCH";
        else if (sinT>0) cout << "LEFT";
        else cout <<"RIGHT";
        cout << endl;
    }

        


}