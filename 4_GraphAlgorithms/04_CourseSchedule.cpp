#include <bits/stdc++.h>
#define ll long long
using namespace std;

void fill_CourseSeq_dfs(int c, int State[], vector <int> Adj[], vector<int> &CourseSeq, bool & impossible){
    if (State[c]==2) return;//Already done in a previous dfs and c is inside CourseSeq
    else if (State[c]==1){
        impossible = true;//Checked again in this dfs... there is a circle...
        return;
    }
    else if (State[c]==0) State[c] = 1;
    
    for (int next_c : Adj[c]){
        fill_CourseSeq_dfs(next_c, State, Adj, CourseSeq, impossible);
        if (impossible) return;        
    }
    CourseSeq.push_back(c);
    State[c] = 2;
}



int main(){
    int n,m,a,b;
    cin >> n >> m;
    vector <int> Adj[n];
    for (int i=0; i<m; i++){
        cin >> a >> b;
        Adj[b-1].push_back(a-1);//if b is completedonly after u can take course a. 
    }

    vector <int> CourseSeq;
    bool impossible = false;
    int State[n]={0};
    for(int c=0;c<n;c++){
        if (State[c]!=0) continue;
        fill_CourseSeq_dfs(c, State, Adj, CourseSeq, impossible);
        if (impossible) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }
    for(int c: CourseSeq) cout << c+1 << " ";
}