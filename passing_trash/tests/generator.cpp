#include <bits/stdc++.h>
#include "testlib.h"
#include "constrains.h"
using namespace std;

void make_sample_testcase(){
    {
        ofstream of("00_sample_01.in");
        of << "3 4" << endl;
        of << "1 2 3" << endl;
        of << "2 1 1" << endl;
        of.close();
    }
}

void make_easy_testcase(int N, ll M, string case_name){
    vector<ll> P(N + 1), Q(N + 1);
    for(int i = 1; i <= N; ++i){
        ll p = rnd.next(MIN_P, MAX_P);
        int q = rnd.next(1, N);
        while(q == i) q = rnd.next(1, N);
        P[i] = p, Q[i] = q;
    }
    ofstream of(case_name.c_str());
    of << N << " " << M << endl;
    for(int i = 1; i <= N; ++i){
        of << P[i] << " \n"[i == N];
    }
    for(int i = 1; i <= N; ++i){
        of << Q[i] << " \n"[i == N];
    }
}

void make_normal_testcase(int N, ll M, string case_name){
    vector<ll> P(N + 1), Q(N + 1);
    for(int i = 1; i <= N; ++i){
        ll p = rnd.next(MIN_P, MAX_P);
        int q = rnd.next(1, N);
        while(q == i) q = rnd.next(1, N);
        P[i] = p, Q[i] = q;
    }
    ofstream of(case_name.c_str());
    of << N << " " << M << endl;
    for(int i = 1; i <= N; ++i){
        of << P[i] << " \n"[i == N];
    }
    for(int i = 1; i <= N; ++i){
        of << Q[i] << " \n"[i == N];
    }
}

void make_hard_testcase(int N, ll M, string case_name){
    vector<ll> P(N + 1), Q(N + 1);
    for(int i = 1; i <= N; ++i){
        ll p = rnd.next(MIN_P, MAX_P);
        int q = rnd.next(1, N);
        while(q == i) q = rnd.next(1, N);
        P[i] = p, Q[i] = q;
    }
    ofstream of(case_name.c_str());
    of << N << " " << M << endl;
    for(int i = 1; i <= N; ++i){
        of << P[i] << " \n"[i == N];
    }
    for(int i = 1; i <= N; ++i){
        of << Q[i] << " \n"[i == N];
    }
}

int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);

    // 00 sample
    make_sample_testcase();

    // 1* Easy
    for(int t = 1; t <= 5; ++t){
        make_easy_testcase(rnd.next(EASY_SMALL_MIN_N, EASY_SMALL_MAX_N), rnd.next(EASY_SMALL_MIN_M, EASY_SMALL_MAX_M), format("10_small_%02d.in", t));
    }
    for(int t = 1; t <= 5; ++t){
        make_easy_testcase(rnd.next(EASY_LARGE_MIN_N, EASY_LARGE_MAX_N), rnd.next(EASY_LARGE_MIN_M, EASY_LARGE_MAX_M), format("11_large_%02d.in", t));
    }
    for(int t = 1; t <= 5; ++t){
        make_easy_testcase(1000, 1000, format("12_max_%02d.in", t));
    }
    {
        ofstream of("13_vicious_01.in");
        of << "1000 1000" << endl;
        for(int i = 1; i <= 1000; ++i) of << 1 << " \n"[i == 1000];
        for(int i = 1; i <= 1000; ++i) of << (i == 1000 ? 1 : i + 1) << " \n"[i == 1000];
        of.close();
    }
    
    // 2* Normal
    for(int t = 1; t <= 5; ++t){
        make_normal_testcase(rnd.next(HARD_SMALL_MIN_N, HARD_SMALL_MAX_N), rnd.next(NORMAL_SMALL_MIN_M, NORMAL_SMALL_MAX_M), format("20_small_%02d.in", t));
    }
    for(int t = 1; t <= 5; ++t){
        make_normal_testcase(rnd.next(HARD_LARGE_MIN_N, HARD_LARGE_MAX_N), rnd.next(NORMAL_LARGE_MIN_M, NORMAL_LARGE_MAX_M), format("21_large_%02d.in", t));
    }
    for(int t = 1; t <= 5; ++t){
        make_normal_testcase(NORMAL_MAX_N, NORMAL_MAX_M, format("22_max_%02d.in", t));
    }
    {
        ofstream of("23_vicious_01.in");
        of << NORMAL_MAX_N << " " << NORMAL_MAX_M << endl;
        for(int i = 1; i <= NORMAL_MAX_N; ++i) of << 1 << " \n"[i == NORMAL_MAX_N];
        for(int i = 1; i <= NORMAL_MAX_N; ++i) of << (i == NORMAL_MAX_N ? 1 : i + 1) << " \n"[i == NORMAL_MAX_N];
        of.close();
    }

    // 3* hard
    for(int t = 1; t <= 5; ++t){
        make_hard_testcase(rnd.next(HARD_SMALL_MIN_N, HARD_SMALL_MAX_N), rnd.next(HARD_SMALL_MIN_M, HARD_SMALL_MAX_M), format("30_small_%02d.in", t));
    }
    for(int t = 1; t <= 5; ++t){
        make_hard_testcase(rnd.next(HARD_LARGE_MIN_N, HARD_LARGE_MAX_N), rnd.next(HARD_LARGE_MIN_M, HARD_LARGE_MAX_M), format("31_large_%02d.in", t));
    }
    for(int t = 1; t <= 5; ++t){
        make_hard_testcase(MAX_N, MAX_M, format("32_max_%02d.in", t));
    }

    return 0;
}