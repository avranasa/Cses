#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <numeric>      // std::iota]
using namespace std;


int main(){
    int n;
    cin >> n;
    vector <int> A(n), B(n), idx(n);
    map <int,int> N_movies;//number of movies up until the "(i-1)-th" movie finishes (ranked by their ending time)
    N_movies[-1] = 0; //initialize 
    for(int i=0; i<n; i++) cin >> A[i] >> B[i];
    iota(idx.begin(), idx.end(), 0);
    stable_sort(idx.begin(), idx.end(), [&B](int i1, int i2){return B[i1] < B[i2];});
    int N_without, N_with;//with and without the last movie
    map <int, int>::iterator iter_begin, iter_end;
    for(int i:idx){
        iter_begin = N_movies.upper_bound(A[i]);
        iter_end = N_movies.upper_bound(B[i]);
        N_with = (--iter_begin)->second + 1;
        N_without = (--iter_end)->second;
        //cout <<"("<<A[i]<<","<<B[i]<<")  "<<N_with<<"  "<< N_without<<endl;
        N_movies[B[i]] = max(N_with, N_without);
    }
    cout << (--N_movies.end())->second;   
}