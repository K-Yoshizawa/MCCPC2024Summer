#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]){
    registerValidation(argc, argv);
    int A = inf.readInt(0, 1000, "A");
    inf.readSpace();
    int B = inf.readInt(0, 1000, "B");
    inf.readSpace();
    int C = inf.readInt(0, 1000, "C");
    inf.readEoln();
    inf.readEof();
    assert(A + B + C >= 1);
    return 0;
}