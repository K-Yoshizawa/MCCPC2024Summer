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
    auto V = inf.readInts(N, 0, 1, "V");
    inf.readEoln();
    UnionFind T(N);
    for(int i = 0; i < N - 1; ++i){
        int A = inf.readInt(1, N, "A_i");
        inf.readSpace();
        int B = inf.readInt(1, N, "B_i");
        inf.readEoln();
        assert(A < B);
        --A, --B;
        assert(T.unite(A, B));
    }
    // int M = inf.readInt(MIN_M, MAX_M, "M");
    // inf.readEoln();
    // bool prev_flag = false;
    // for(int i = 1; i <= M; ++i){
    //     if(prev_flag){
    //         inf.readInt(1, N, format("Q_%d", i));
    //         prev_flag = false;
    //     }
    //     else{
    //         prev_flag = (inf.readInt(0, N, format("Q_%d", i)) == 0);
    //     }
    //     if(i < M) inf.readSpace();
    // }
    // inf.readEoln();
    inf.readEof();
    return 0;
}