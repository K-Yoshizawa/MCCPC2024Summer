#include <bits/stdc++.h>
#include "testlib.h"
#include "constrains.h"
using namespace std;

struct UnionFind {
    vector< int > data;
    
    UnionFind(int sz) {
        data.assign(sz, -1);
    }
    
    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if(x == y) return (false);
        if(data[x] > data[y]) swap(x, y);
        data[x] += data[y];
        data[y] = x;
        return (true);
    }
    
    int find(int k) {
        if(data[k] < 0) return (k);
        return (data[k] = find(data[k]));
    }
};

int main(int argc, char* argv[]){
    registerValidation(argc, argv);
    int N = inf.readInt(MIN_N, MAX_N, "N");
    inf.readEoln();
    int missing = 0;
    UnionFind uf(N + 1);
    for(int i = 1; i <= N; ++i){
        int u = inf.readInt(1, N, format("u_%d", i));
        inf.readSpace();
        int v = inf.readInt(u + 1, N, format("v_%d", i));
        inf.readEoln();
        if(!uf.unite(u, v)) ++missing;
    }
    ensure(missing == 1);
    int T = inf.readInt(MIN_T, MAX_T, "T");
    inf.readEoln();
    for(int i = 1; i <= T; ++i){
        int A = inf.readInt(1, N, "A");
        inf.readSpace();
        int B = inf.readInt(1, N, "B");
        inf.readEoln();
        ensure(A != B);
    }
    inf.readEof();
    return 0;
}