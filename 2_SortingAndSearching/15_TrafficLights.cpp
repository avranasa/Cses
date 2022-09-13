#include <iostream>
#include <unordered_map>
#include <set>
#include <queue>
#include <algorithm>
#include <list>

using namespace std;


//using a map is TOO slow... each search for an element (or adding or erasing element) takes a lot of time so it cannot be repeated 200000 times
//Go for unordered map + a heap 
int main(){
    unordered_map <int, int> Length; //for each length it stores the number of times this length between lights appear
    unordered_map <int, int> ::iterator Map_it;
    priority_queue <int> max_length;
    
    int n,x, p, prev_light, next_light, d;
    pair<set<int>::iterator,bool> ret;
    set <int> Lights;
    /*
    list <int> Lights; // Even though inserting a new light is very fast ... finding where
                    //to insert it is slow even with the "it_lights = upper_bound(Lights.begin(), Lights.end(), p);"
                    //that is logarithmic in complexity. Better use set.
    list <int>::iterator it_lights;
    Lights.push_back(0);
    Lights.push_back(x); */
    cin >> x >> n;
    Length[x] = 1;
    max_length.push(x);
    Lights.insert(0);
    Lights.insert(x);
    for (int i=1; i<=n; i++){
        cin >> p;
        ret = Lights.insert(p);
         
        ret.first ++;
        next_light = (*ret.first);
        ret.first --;ret.first --;
        prev_light = (*ret.first);
       
        Map_it = Length.find(next_light - prev_light);
        Map_it->second --;
        if ( Map_it->second == 0) Length.erase( Map_it ); 
        d = next_light-p;
        Map_it = Length.find(d);
        if (Map_it == Length.end()) {
            Length[d] = 1;
            max_length.push(d);
        }
        else  Map_it->second ++;
        d = p-prev_light;
        Map_it = Length.find(d);
        if (Map_it == Length.end()) {
            Length[d] = 1;
            max_length.push(d);
        }
        else  Map_it->second ++;
        

        while (true){
            d = max_length.top();
            if (Length.count(d)>0){
                cout << d <<" ";
                break;
            }
            else max_length.pop();
        }

    }
}