#include <bits/stdc++.h>
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
#define int long long
using namespace std;
const long long inf = 1LL<<60; //1.5e18, max(long long)= 9e18 = 2^63
const int md = 1000000007;

int Less180(int x1, int y1, int x2, int y2, int x3, int y3){
    //Retruns 1 if the right hand angle (x1,y1)-(x2,y2)-(x3,y3) is less than 180 degrees
    //and -1 if it is more and 0 if it is exactly.
    int dx1 = x2-x1, dy1=y2-y1, dx2=x3-x2, dy2=y3-y2;
    //Key ideas: i) the vector (-dy,dx) forms 90 degrees right hand angle seen from vector (dx,dy) ...
    // ii) the sign of the dot product of the angle between two vectors is less or more than 90 degrees
    if  (dy1*dx2 - dx1*dy2  > 0) return 1;
    else if (dy1*dx2 - dx1*dy2  < 0) return -1;
    else if (dx1*dx2>=0 && dy1*dy2>=0) return 2;//(x1,y1), (x2,y2), (x3,y3) are on the same line  and (x2,y2) in the middle
    else return -2;    //(x1,y1), (x2,y2), (x3,y3) are on the same line  and (x2,y2) not in the middle
}

signed main(){
    int t, x1, y1, x2, y2, x3, y3, x4, y4, p1, p2, p3, p4;
    cin >> t;
    for( int i=0; i<t; i++){
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
        p1 = Less180(x1,y1,x3,y3,x2,y2);        
        p2 = Less180(x3,y3,x2,y2,x4,y4);        
        p3 = Less180(x2,y2,x4,y4,x1,y1);
        p4 = Less180(x4,y4,x1,y1,x3,y3);
        if (p1==2 || p2==2 || p3==2 || p4==2) cout <<"YES" _endl;//one end-point is on the others line segment
        else if (p1==-2 || p2==-2 || p3==-2 || p4==-2) cout <<"NO" _endl;
        else if (p1*p2>0 && p2*p3>0 && p3*p4>0) cout <<"YES" _endl;
        else  cout << "NO" _endl;
    }   
    //A second (probably easier conceived) method is to find the if the line segment are parallel and if
    //not to find if the common point of their line extension is also a point of any of those segments
}