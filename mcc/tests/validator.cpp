#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]){
    registerValidation(argc, argv);
    inf.readToken("[A-Z]{1, 1}", "A");
    inf.readSpace();
    inf.readToken("[A-Z]{1, 1}", "B");
    inf.readEoln();
    inf.readEof();
    return 0;
}