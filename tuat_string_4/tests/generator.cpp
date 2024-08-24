#include <bits/stdc++.h>
#include "testlib.h"
#include "constrains.h"
using namespace std;

void make_sample_testcase(){
    {
        ofstream of("00_sample_01.in");
        of << "9 26" << endl;
        of << "16 18 15 3 5 19 19 15 18" << endl;
        of.close();
    }
    {
        ofstream of("00_sample_02.in");
        of << "4 26" << endl;
        of << "20 21 1 20" << endl;
        of.close();
    }
    {
        ofstream of("00_sample_03.in");
        of << "11 26" << endl;
        of << "13 9 19 19 9 19 19 9 16 16 9" << endl;
        of.close();
    }
}

void make_testcase(int N, int M, string case_name){
    ofstream of(case_name.c_str());
    of << N << " " << M << endl;
    for(int i = 1; i <= N; ++i){
        of << rnd.next(1, M) << " \n"[i == N];
    }
    of.close();
}

int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);

    make_sample_testcase();

    for(int t = 1; t <= 7; ++t){
        make_testcase(rnd.next(EASY_RND_MIN_N, EASY_RND_MAX_N), 26, format("11_random_%02d.in", t));
    }
    for(int t = 1; t <= 3; ++t){
        make_testcase(rnd.next(EASY_MAX_N, EASY_MAX_N), 26, format("12_max_%02d.in", t));
    }
    {
        ofstream of("13_min_01.in");
        of << "4 26" << endl;
        of << "20 1 21 20" << endl;
        of.close();
    }
    {
        ofstream of("13_min_02.in");
        of << "4 26" << endl;
        of << "1 1 20 21" << endl;
        of.close();
    }
    {
        ofstream of("13_min_03.in");
        of << "4 26" << endl;
        of << "1 20 21 21" << endl;
        of.close();
    }

    for(int t = 1; t <= 7; ++t){
        make_testcase(rnd.next(LARGE_MIN_N, LARGE_MAX_N), 26, format("21_random_%02d.in", t));
    }
    for(int t = 1; t <= 3; ++t){
        make_testcase(MAX_N, 26, format("22_max_%02d.in", t));
    }

    for(int t = 1; t <= 10; ++t){
        make_testcase(rnd.next(LARGE_MIN_N, LARGE_MAX_N), rnd.next(LARGE_MIN_M, LARGE_MAX_M), format("31_random_%02d.in", t));
    }
    for(int t = 1; t <= 5; ++t){
        make_testcase(MAX_N, MIN_M, format("32_max_dense_%02d.in", t));
    }
    for(int t = 1; t <= 5; ++t){
        make_testcase(MAX_N, MAX_M, format("33_max_sparse_%02d.in", t));
    }

    return 0;
}