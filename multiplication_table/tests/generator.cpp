#include <bits/stdc++.h>
#include "testlib.h"
#include "constrains.h"
using namespace std;

void make_sample_testcase(){
    {
        ofstream of("00_sample_01.in");
        of << "4 4" << endl;
        of.close();
    }
    {
        ofstream of("00_sample_02.in");
        of << "3 9" << endl;
        of.close();
    }
    {
        ofstream of("00_sample_03.in");
        of << "5 12345678901234567890" << endl;
        of.close();
    }
}

void make_easy_testcase(int N, string case_name){
    int M = rnd.next(4, EASY_MAX_M - N);
    ofstream of(case_name.c_str());
    of << N << " " << M << endl;
    of.close();
}

void make_hard_testcase(int N, int M_digit, string case_name){
    string M = rnd.next(format("[1-9][0-9]{%d,%d}", M_digit - 1, M_digit - 1));
    ofstream of(case_name.c_str());
    of << N << " " << M << endl;
    of.close();
}

int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);

    // 00 sample
    make_sample_testcase();

    // 1* Easy
    for(int t = 1; t <= 10; ++t){
        make_easy_testcase(rnd.next(MIN_N, EASY_MAX_N), format("10_random_%02d.in", t));
    }

    // 2* hard
    for(int t = 1; t <= 20; ++t){
        make_hard_testcase(rnd.next(MIN_N, MAX_N), rnd.next(MIN_M, MAX_M), format("20_random_%02d.in", t));
    }
    for(int t = 1; t <= 5; ++t){
        make_hard_testcase(MAX_N, MAX_M, format("21_max_%02d.in", t));
    }
    {
        ofstream of("22_hand_01.in");
        of << "1 0" << endl;
        of.close();
    }
    {
        ofstream of("22_hand_02.in");
        of << "9 0" << endl;
        of.close();
    }
    {
        ofstream of("22_hand_03.in");
        of << "3000 1" << rnd.next("[0]{99999}") << endl;
        of.close();
    }

    return 0;
}