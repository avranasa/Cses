#include <iostream>
#include <math.h>
using namespace std;

void move(int Ndisks, int FromStack, int ToStack){
    if (Ndisks==1) cout <<FromStack <<' '<<ToStack<<'\n';
    else{
        int ThroughStack;
        if (FromStack+ToStack == 3) ThroughStack = 3;
        if (FromStack+ToStack == 4) ThroughStack = 2;
        if (FromStack+ToStack == 5) ThroughStack = 1;    

        move(Ndisks-1, FromStack, ThroughStack);
        cout << FromStack <<' '<< ToStack <<'\n';
        move(Ndisks-1, ThroughStack, ToStack);
    }
}

int main(){
    int Ndisks;
    cin >> Ndisks;
    cout << pow(2,Ndisks)-1<<'\n';
    move(Ndisks, 1, 3);
}