#include <bits/stdc++.h>
#include "testlib.h"
#include "constrains.h"
using namespace std;

int main(int argc, char* argv[]){
    registerValidation(argc, argv);
    int T = inf.readInt(MIN_T, MAX_T, "T");
    inf.readEoln();
    for(int i = 0; i < T; ++i){
        int N = inf.readInt(MIN_N, MAX_N, "N");
        inf.readSpace();
        int M = inf.readInt(MIN_M, MAX_M, "M");
        inf.readSpace();
        int K = inf.readInt(MIN_K, N - 1, "K");
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}