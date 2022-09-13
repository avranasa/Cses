#include <iostream>
using namespace std;

int main(){
    int N, x1,x2, c1, c2;
    cin >> N ;
    //If n1 times you use the first move and n2 times the second one then if you start adding coins to create the piles 
    //you will have n1+2*n2 coins in the first pile and 2*n1+n2 piles in the second.... solve the linear system
    for (int i =0; i<N; i++){
        cin >> x1 >> x2;
        c1 = 2*x1-x2;
        c2 = 2*x2-x1;
        if ((c1%3 == 0) && (c2%3 == 0) && (c1>=0) && (c2>=0)) cout<<"YES";
        else cout<<"NO";
        cout <<"\n";
    }
}