#include <bits/stdc++.h>
using namespace std;
//Read first Range Queries and then recheck them


//Think of the problem in 2D where each bracket is a point
int main(){
    int n;
    cin >>n;
    int a, b, Contains[n]={}, Contained[n]={}, TimeIntervals[n][2];
    map <int, int> StartTime;
    map <int, int> EndTime;
    map <int, int> :: iterator itET;
    for (int i=0; i<n; i++){
        cin >>a >> b;
        StartTime[a] = i;
        EndTime[b] = i;
        TimeIntervals[i][0] = a;
        TimeIntervals[i][1] = b;
    }
    int ET, i_st, i_end;
    for (auto &st:StartTime){
        i_st = st.second;
        ET = TimeIntervals[i_st][1];
        itET = EndTime.find(ET);
        itET --;
        for(auto it:itET; it==EndTime.begin(); it--){
            i_end = EndTime[];
            
        }
    }

}


/*it is too slow...
int main(){
    int n, a, a_new, b_new, b;
    cin >>n;
    int TimesIntervals[n][2], Contains[n]={}, Contained[n]={};
    for (int i=0; i<n; i++){
        cin >> a >> b;
        TimesIntervals[i][0] = a;
        TimesIntervals[i][1] = b;
        for(int j=0;j<i; j++){
            a_new = TimesIntervals[j][0];
            b_new = TimesIntervals[j][1];
            if ((a<= a_new) && (b>=b_new)) {
                Contains[i] ++;
                Contained[j] ++;
            }
            if ((a>= a_new) && (b<=b_new)) {
                Contains[j] ++;
                Contained[i] ++;
            }
        }
    }
    for (int c:Contains) cout << c<<" ";
    cout <<endl;
    for (int c:Contained) cout << c<<" ";

}
*/




/*
//The code below does not work... 
//If you  know that between an interval there are 3x[ and 3x] it can
//be either that it contains 3 ranges or 0...
int main(){
    int n, a, b;
    cin >>n;
    int TimesIntervals[n][2];
    multimap <int, pair<bool,int>> BracketPerTime;
    for (int i=0; i<n; i++){
        cin >> a >> b;
        TimesIntervals[i][0] = a;
        TimesIntervals[i][1] = b;
        BracketPerTime.insert({a,{true,i}});
        BracketPerTime.insert({b,{false,i}});
    }

    unordered_map <int,vector <int>> CountBrackets;
    int CountCloseBracket=0, CountOpenBracket=0, ReverseCountCloseBracket=0, ReverseCountOpenBracket=0, time;
    for (auto it=BracketPerTime.begin(); it!=BracketPerTime.end(); it++){
        auto p = it->second;
        time = it->first;
        if (p.first) CountOpenBracket ++;
        else CountCloseBracket ++;
        if (!CountBrackets.count(time)) CountBrackets[time] = {0,0,0,0};
        CountBrackets[time][0] = CountOpenBracket;
        CountBrackets[time][1] = CountCloseBracket;
    }
    for (auto it=BracketPerTime.rbegin(); it!=BracketPerTime.rend(); it++){
        auto p = it->second;
        time = it->first;
        if (p.first) ReverseCountOpenBracket ++;
        else ReverseCountCloseBracket ++;
        CountBrackets[time][2] = ReverseCountOpenBracket;
        CountBrackets[time][3] = ReverseCountCloseBracket;
    }

    for(int i=0;i<n;i++){
        a = TimesIntervals[i][0];
        b = TimesIntervals[i][1];
        cout
    }
     
}*/