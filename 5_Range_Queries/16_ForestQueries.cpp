#include <bits/stdc++.h>
#define ff first
#define ss second
#define _endl <<'\n'
#define _space <<' '
#define _space_ <<' '<<
using namespace std;
const int md = 1000000007;

int tree[2000][2000]={0}; //It is a segment tree of segment trees. Each row corresponds to a 
//range of "rows" of the forest. If for example the i-th element corresponds to the rows
//[y1,y2] (keeping the notation of the problem) then the tree[i] is a segment tree that 
//each tree[i][j] element corresponds to a rectangular ...
//In the beginning there is not tree!

int sum_1D(int i, int x1, int x2, int n){
    int s=0;
    x1+=n; x2+=n; //input & output of indexing assumed to start from 1;
    while (x1<=x2) {
        if (x1%2==1) s += tree[i][x1++];
        if (x2%2==0) s += tree[i][x2--];
        x1/=2; x2/=2;
    }
    return s; 
}

int sum_2D(int y1, int x1, int y2, int x2, int n){
    int s=0;
    y1+=n; y2+=n; //input & output of indexing assumed to start from 1;
    while (y1<=y2) {
        if (y1%2==1) s += sum_1D(y1++, x1, x2, n); 
        if (y2%2==0) s += sum_1D(y2--, x1, x2, n); 
        y1/=2; y2/=2;
    }
    return s;  
}

void update_1D(int i, int x, int n, int upd){
    x += n;
    tree[i][x] += upd;
    for (x/=2; x>=1; x/=2) tree[i][x] += upd;
}

void update_2D(int y, int x, int n){
    y += n;
    int upd = tree[y][x+n]==0 ? 1 : -1;//if 0 in the position [y,x] there 
                    //was no tree, so we add on. Otherwise we remove one
    update_1D(y, x, n, upd);
    for (y/=2; y>=1; y/=2) update_1D(y, x, n, upd);
}

int main(){    
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    int n, q, y1, x1, y2, x2, k;
    char c;
    cin >> n >> q;
    for (int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> c;
            if (c=='*') update_2D(i, j, n);
        }
    }

    for(int i=0; i<q; i++){
        cin >> k >> y1 >> x1;
        if (k==1) update_2D(y1-1, x1-1, n);
        if (k==2){
            cin >> y2 >> x2;
            cout << sum_2D(y1-1, x1-1, y2-1, x2-1, n) _endl;
        }
    }

}