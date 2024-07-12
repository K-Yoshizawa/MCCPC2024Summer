#include <bits/stdc++.h>
#include "testlib.h"
#include "constrains.h"
using namespace std;

int main(int argc, char* argv[]){
    registerValidation(argc, argv);
    int N = inf.readInt(MIN_N, MAX_N, "N");
    inf.readSpace();
    ll M = inf.readLong(MIN_M, MAX_M, "M");
    inf.readEoln();
    auto P = inf.readLongs(N, MIN_P, MAX_P, "P");
    inf.readEoln();
    auto Q = inf.readInts(N, MIN_Q, N, "Q");
    inf.readEoln();
    for(int i = 0; i < N; ++i){
        assert(Q[i] != i + 1);
    }
    inf.readEof();
    return 0;
}