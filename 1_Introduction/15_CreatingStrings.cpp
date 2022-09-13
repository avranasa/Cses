#include <iostream>
#include <map>
#include <vector>
using namespace std;

void PlaceChar(int n, int N, map<char,int> LetterFreq, vector <char> Placement){
    if (n==N){
        for (auto const & x: Placement) cout << x;
        cout << endl;
        return;
    }
    

    for(auto const& L: LetterFreq){//check if it works witohut  const
        if (L.second > 0){
            map <char, int> NewLetterFreq(LetterFreq) ;
            NewLetterFreq[L.first] --;
            Placement[n] = L.first;
            PlaceChar(n+1, N, NewLetterFreq, Placement);  
        }          
    }
}


int NchooseR(int n, int r){
    if (r == 0) return 1;
    if (r > n / 2) return NchooseR(n, n - r); 

    long res = 1; 

    for (int k = 1; k <= r; ++k)  res = ( (n - k + 1)*res )/ k;
    return res;
}

int main(){
    map <char, int> LetterFreq ;
    char c; 
    int N=0;

    while (cin>>c){
        if (LetterFreq.count(c)==0) LetterFreq[c]=1;
        else LetterFreq[c]++;
        N++;
    }
    vector <char> Placement(N);

    int totalComb=1, Nchar=0;
    for( auto const &L: LetterFreq){
        Nchar += L.second;
        totalComb *= NchooseR(Nchar, L.second);    
    }
    cout << totalComb <<endl;
    PlaceChar(0, N, LetterFreq, Placement);
}




/*
void placeAnElement(vector<char> FreeChars, map <char, int> LetterFreq, vector<int> FreePos, vector<char> Placement){
    if (FreeChars.empty()){
        for (auto const & x : Placement) cout<<x;
        cout <<  endl;
        return;
    }

    char elem = FreeChars.back();
    int Kelem = LetterFreq[elem], garbage;
    vector <char> NewFreeChars(FreeChars.begin(),FreeChars.end()-1);

    do{
        vector <int> NewFreePos(FreePos.begin()+Kelem, FreePos.end());
        for(int i=0; i<Kelem; ++i) Placement[FreePos[i]]=elem;

        cout <<"\nNew Round"<<endl;
        for (auto const & x: NewFreePos) cout<<x<<" ";
        cout << endl;
        for (auto const & x: Placement) cout<<x<<" ";
        cout << endl;

        //placeAnElement(NewFreeChars, LetterFreq, NewFreePos, Placement);
    }while (prev_permutation(FreePos.begin(),FreePos.end()));    
}

int main(){
    map <char, int> LetterFreq ;
    vector <int> FreePos;
    vector <char> FreeChars;
    char c; 
    int n=0;

    while (cin>>c){
        if (LetterFreq.count(c)==0) {
            LetterFreq[c]=1;
            FreeChars.push_back(c);
        }
        else LetterFreq[c]++;
        FreePos.push_back(n);
        n++;
    }
    vector <char> Placement(n,'.');
    placeAnElement(FreeChars, LetterFreq, FreePos, Placement);
}
*/
