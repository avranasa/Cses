#include <iostream>
#include <queue>
#include <set>
#include <cassert>
using namespace std;

int main(){
    int n,k, n_max=0;
    set <int> Songs;
    queue <int> Seq_Songs;
    cin >> n;
    for (int i=0;i<n;i++){
        cin >> k;
        auto res = Songs.insert(k);
        Seq_Songs.push(k);
        if (!res.second) {
            n_max = max(n_max, (int)Songs.size());
            while(Seq_Songs.front()!=k){
                Songs.erase(Seq_Songs.front());
                Seq_Songs.pop();
            }
            Seq_Songs.pop();//to delete even the song k
        }   
        assert(Songs.size() == Seq_Songs.size()); 
    }
    n_max = max(n_max,(int) Songs.size());
    cout << n_max;
}