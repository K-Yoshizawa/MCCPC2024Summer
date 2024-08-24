#include <bits/stdc++.h>
#include "testlib.h"
#include "constrains.h"
using namespace std;

int main(int argc, char* argv[]){
    registerValidation(argc, argv);
    int N = inf.readInt(MIN_N, MAX_N, "N");
    inf.readSpace();
    int M = inf.readInt(MIN_M, MAX_M, "M");
    inf.readEoln();
    auto C = inf.readInts(N, 1, M, "C");
    inf.readEoln();
    inf.readEof();
    return 0;
}