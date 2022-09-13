#include <iostream>
#include <vector>
#include <bitset>
#include <queue>
using namespace std;

#define N 3//number of squares per edge

void F( queue <int> &Q){
    Q.push(4);
}

int main(){
    bitset<10> s= 154;
    for (int i=0;i<8;i++) cout<<s[i]<<endl;
}

