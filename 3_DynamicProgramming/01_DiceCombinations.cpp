#include <iostream>
#include <deque>
using namespace std;

int main(){
    deque <long long> F = {1,2,4,8,16,32};
    long long n, newF;
    cin >> n;
    if (n<=6){
        cout << F[n-1];
        return 0;
    }
    for(int i=7;i<=n;i++){
        newF=0;
        for( int q=0;q<6;q++) newF+=F[q];
        newF %= 1000000007;
        F.push_back(newF);
        F.pop_front();        
        //for (auto q:F) cout <<q<<"  ";
        //cout << endl;
    }
    cout << newF;
}