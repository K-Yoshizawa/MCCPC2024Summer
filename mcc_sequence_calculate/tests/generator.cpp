#include <bits/stdc++.h>
#include "testlib.h"
#include "constrains.h"
using namespace std;

void make_sample_testcase(){
    {
        ofstream of("00_sample_01.in");
        of << "5" << endl;
        of << "1 2 2 3 3" << endl;
        of.close();
    }
}

void make_testcase(int N, string case_name){
    ofstream of(case_name.c_str());
    of << N << endl;
    for(int i = 1; i <= N; ++i){
        of << rnd.next(1, N) << " \n"[i == N];
    }
    of.close();
}

int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);

    // 00 sample
    make_sample_testcase();

    // 1* Easy
    for(int t = 1; t <= 7; ++t){
        make_testcase(rnd.next(EASY_LARGE_MIN_N, EASY_LARGE_MAX_N), format("11_random_%02d.in", t));
    }
    for(int t = 1; t <= 3; ++t){
        make_testcase(EASY_MAX_N, format("12_max_%02d.in", t));
    }
    {
        ofstream of("13_min_01.in");
        of << "3" << endl;
        of << "1 2 2" << endl;
        of.close();
    }
    {
        ofstream of("13_min_02.in");
        of << "3" << endl;
        of << "2 1 2" << endl;
        of.close();
    }
    {
        ofstream of("13_min_03.in");
        of << "3" << endl;
        of << "2 2 1" << endl;
        of.close();
    }
    {
        ofstream of("13_min_04.in");
        of << "3" << endl;
        of << "1 1 1" << endl;
        of.close();
    }

    // 2* Normal
    for(int t = 1; t <= 7; ++t){
        make_testcase(rnd.next(NORMAL_LARGE_MIN_N, NORMAL_LARGE_MAX_N), format("21_random_%02d.in", t));
    }
    for(int t = 1; t <= 3; ++t){
        make_testcase(NORMAL_MAX_N, format("22_max_%02d.in", t));
    }

    // 3* Hard
    for(int t = 1; t <= 7; ++t){
        make_testcase(rnd.next(HARD_LARGE_MIN_N, HARD_LARGE_MAX_N), format("31_random_%02d.in", t));
    }
    for(int t = 1; t <= 3; ++t){
        make_testcase(MAX_N, format("32_max_%02d.in", t));
    }

    return 0;
}