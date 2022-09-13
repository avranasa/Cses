#include <iostream>
#include <vector>

using namespace std;

int main(){
    int x, max_d, aux, r=0;
    cin >> x;
    while (x>0){
        r ++;
        aux=x;
        max_d = 0;
        do{
            max_d = max(max_d, aux%10);
            aux /= 10;
        }while(aux>0);
        x -= max_d;
    }
    cout << r;
}