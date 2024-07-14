#include <bits/stdc++.h>
#include "testlib.h"
#include "constrains.h"
using namespace std;

int main(int argc, char* argv[]){
    registerValidation(argc, argv);
    int N = inf.readInt(MIN_N, MAX_N, "N");
    inf.readEoln();
    inf.readToken(format("[a-z]{%d, %d}", N, N), "S");
    inf.readEoln();
    inf.readEof();
    return 0;
}