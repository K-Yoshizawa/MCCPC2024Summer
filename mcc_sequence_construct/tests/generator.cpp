#include <bits/stdc++.h>
#include "testlib.h"
#include "constrains.h"
using namespace std;

void make_sample_testcase(){
    {
        ofstream of("00_sample_01.in");
        of << "10" << endl;
        of.close();
    }
}

int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);

    // 00 sample
    make_sample_testcase();

    // 1* Easy
    for(int t = 0; t <= 5; ++t){
        ofstream of(format("10_M_equals_%02d.in", t));
        of << t << endl;
        of.close();
    }

    // 2* hard
    for(int t = HARD_SMALL_MIN_M; t <= HARD_SMALL_MAX_M; ++t){
        ofstream of(format("20_small_%02d.in", t - HARD_SMALL_MIN_M + 1));
        of << t << endl;
        of.close();
    }
    for(int t = 1; t <= 20; ++t){
        ofstream of(format("21_medium_%02d.in", t));
        of << rnd.next(HARD_MEDIUM_MIN_M, HARD_MEDIUM_MAX_M) << endl;
        of.close();
    }
    for(int t = 1; t <= 20; ++t){
        ofstream of(format("22_large_%02d.in", t));
        of << rnd.next(HARD_LARGE_MIN_M, HARD_LARGE_MAX_M) << endl;
        of.close();
    }
    {
        ofstream of(format("23_max_01.in"));
        of << MAX_M << endl;
        of.close();
    }

    return 0;
}