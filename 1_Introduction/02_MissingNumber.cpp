#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

int main()
{   
    unordered_set <int> S;
    long int N, x;
    cin >> N;
    for (int i = 1; i < N; ++i) {
        cin >> x;
        S.insert(x);
    }
    for (int i = 1; i <= N; ++i){
        if (!S.count(i)){
            cout << i;
            break;
        }
    }
    cout << endl;
}