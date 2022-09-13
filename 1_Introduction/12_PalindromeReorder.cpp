#include <iostream>
#include <map>

using namespace std;

int main(){
    map <char, int> M;
    char c;
    while (cin >> c){
        if (M.count(c)==0) M[c] = 1;
        else M[c]++;
    }
    char chOdd;
    int oddCounter = 0, N_repetOdd = 0;
    for ( auto iter=M.begin(); iter!=M.end(); ++iter){
        if (iter->second % 2 == 1){
            chOdd = iter->first;
            N_repetOdd = iter->second;
            oddCounter += 1;            
        } 
    }
    if (oddCounter>1) cout<< "NO SOLUTION";
    else{
        for (auto it = M.begin(); it!=M.end(); ++it)
            for(int i=0; i<it->second/2; i++) 
                if (it->first !=chOdd) cout << it->first;
        if (oddCounter==1) for (int i=0; i<N_repetOdd; i++) cout <<chOdd;        
        for (auto it = M.rbegin(); it!=M.rend();++it)
            for(int i=0; i<it->second/2; i++) 
                if (it->first !=chOdd) cout << it->first;
    }
}