#include <bits/stdc++.h>
#include "testlib.h"
#include "constrains.h"
using namespace std;

void make_sample_testcase(){
    {
        ofstream of("00_sample_01.in");
        of << "2" << endl;
        of << "3 2 1" << endl;
        of << "2 10 0" << endl;
        of.close();
    }
}

void make_easy_testcase(int T, string case_name){
    ofstream of(case_name.c_str());
    of << T << endl;
    for(int i = 0; i < T; ++i){
        int N = rnd.next(MIN_N, EASY_MAX_N);
        int M = rnd.next(0, int(log(EASY_MAX_A) / log(N)));
        int A = 1;
        for(int i = 0; i < M; ++i) A *= N;
        int K = rnd.next(0, min(N - 1, EASY_MAX_A - A));
        of << N << " " << M << " " << K << endl;
    }
    of.close();
}

void make_hard_testcase(int T, string case_name){
    ofstream of(case_name.c_str());
    of << T << endl;
    for(int i = 0; i < T; ++i){
        int N = rnd.next(MIN_N, MAX_N);
        int M = rnd.next(MIN_M, MAX_M);
        int K = rnd.next(0, N - 1);
        of << N << " " << M << " " << K << endl;
    }
    of.close();
}

int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);

    // 00 sample
    make_sample_testcase();

    // 1* Easy
    for(int t = 1; t <= 10; ++t){
        make_easy_testcase(rnd.next(MIN_T, EASY_MAX_T), format("10_random_%02d.in", t));
    }
    {
        ofstream of("11_hand_01.in");
        of << "10" << endl;
        of << "2 0 0" << endl;
        of << "2 0 1" << endl;
        of << "3 0 0" << endl;
        of << "3 0 1" << endl;
        of << "3 0 2" << endl;
        of << "4 0 0" << endl;
        of << "4 0 1" << endl;
        of << "4 0 2" << endl;
        of << "4 0 3" << endl;
        of << "5 5 4" << endl;
        of.close();
    }

    // 2* hard
    for(int t = 1; t <= 10; ++t){
        make_hard_testcase(rnd.next(MIN_T, MAX_T), format("20_random_%02d.in", t));
    }
    for(int t = 1; t <= 10; ++t){
        make_hard_testcase(MAX_T, format("21_max_%02d.in", t));
    }
    {
        ofstream of("22_hand_01.in");
        of << "200000" << endl;
        of << MAX_N << " " << MAX_M << " " << MAX_N - 1 << endl;
        for(int i = 2; i <= 200000; ++i){
            int N = rnd.next(MAX_N / 10, MAX_N);
            of << N << " " << rnd.next(MIN_M, MAX_M) << " " << N - 1 << endl;
        }
        of.close();
    }

    return 0;
}