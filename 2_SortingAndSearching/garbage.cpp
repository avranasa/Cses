#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <tuple>
#include <queue>
using namespace std;

int main(){
	vector <int> X={1,4};
	vector <int> ::iterator it;
	it = X.begin();
	it --;
	for(auto g= it; g==X.begin(); g--) cout << "yolo\n";
} 
