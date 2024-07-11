#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);
    array<char, 26> alpha;
    iota(alpha.begin(), alpha.end(), 'A');
    for(int t = 0; t < 5; ++t){
        shuffle(alpha.begin(), alpha.end());
        ofstream of(format("01_diff_%02d.in", t + 1).c_str());
        of << alpha[0] << " " << alpha[1] << endl;
        of.close();
    }
    for(int t = 0; t < 5; ++t){
        shuffle(alpha.begin(), alpha.end());
        ofstream of(format("02_same_%02d.in", t + 1).c_str());
        of << alpha[0] << " " << alpha[0] << endl;
        of.close();
    }
    return 0;
}