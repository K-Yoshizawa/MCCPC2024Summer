#include <bits/stdc++.h>
#include "testlib.h"
#include "constrains.h"
using namespace std;

int main(int argc, char* argv[]){
    registerValidation(argc, argv);
    inf.readInt(MIN_N, MAX_N, "N");
    inf.readSpace();
    inf.readToken("[1-9][0-9]{0,99999}", "M");
    inf.readEoln();
    inf.readEof();
    return 0;
}