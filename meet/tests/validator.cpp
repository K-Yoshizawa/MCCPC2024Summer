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
    inf.readSpace();
    int M = inf.readInt(N - 1, MAX_M, "M");
    inf.readEoln();
    UnionFind uf(N + 1);
    for(int i = 0; i < M; ++i){
        int A = inf.readInt(1, N, "A");
        inf.readSpace();
        int B = inf.readInt(A + 1, N, "B");
        inf.readSpace();
        int C = inf.readInt(MIN_C, MAX_C, "C");
        inf.readEoln();
    }
    int T = inf.readInt(MIN_T, MAX_T, "T");
    inf.readEoln();
    auto K = inf.readInts(T, 0, MAX_K, "K");
    inf.readEoln();
    inf.readEof();
    return 0;
}