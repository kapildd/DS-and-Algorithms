//
// Created by kapildd on 8/1/17.
//

#include<iostream>
#include<cassert>
#define SZ 10000

using namespace std;

int Rank[SZ], Parent[SZ];

//Find the root of the tree in which x lies
int Find(int x) {
    if(Parent[x] == x) {
        return x;
    }
    return Parent[x] = Find(Parent[x]); ///path compression
}
//Join two trees, if x and y belong to two different trees
void Union(int x, int y) {
    x = Find(x);
    y = Find(y);
    if(x == y) return;

    if(Rank[x] >= Rank[y]) {
        Parent[y] = x;
        if(Rank[x]==Rank[y])
            Rank[x] += 1;
    }else{
        Parent[x] = y;
    }
}

int main(){
    int n;
    cin>>n;
    assert(n<SZ);
    for(int i=0; i<n; i++) {
        Rank[i] = 0;
        Parent[i] = i;
    }
    int q;
    cin>>q;
    for(int i=0; i<q; i++) {
        int query_type, x, y;
        cin>>query_type >> x >> y;
        if(query_type == 0) {
            //Find whether two elements belong to same set
            cout << (Find(x)==Find(y) ? "YES" : "NO") << endl;
        }else{
            //Merge sets containing x and y
            Union(x, y);
        }
    }
    return 0;
}