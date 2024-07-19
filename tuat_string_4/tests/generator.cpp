#include <bits/stdc++.h>
#include "testlib.h"
#include "constrains.h"
using namespace std;

void make_sample_testcase(){
    {
        ofstream of("00_sample_01.in");
        of << "10" << endl;
        of << "tuatuatuat" << endl;
        of.close();
    }
    {
        ofstream of("00_sample_02.in");
        of << "4" << endl;
        of << "tuat" << endl;
        of.close();
    }
    {
        ofstream of("00_sample_03.in");
        of << "11" << endl;
        of << "mississippi" << endl;
        of.close();
    }
}

void make_easy_testcase(int N, string case_name){
    array<char, 26> alpha;
    iota(alpha.begin(), alpha.end(), 'a');
    shuffle(alpha.begin(), alpha.end());
    string S = rnd.next(format("[%c%c%c]{%d}", alpha[0], alpha[1], alpha[2], N));
    ofstream of(case_name.c_str());
    of << N << endl;
    of << S << endl;
    of.close();
}

void make_hard_testcase(int N, string case_name, string pattern = "a-z"){
    string S = rnd.next(format("[%s]{%d}", pattern.c_str(), N));
    ofstream of(case_name.c_str());
    of << N << endl;
    of << S << endl;
    of.close();
}

int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);

    make_sample_testcase();

    for(int t = 1; t <= 10; ++t){
        make_easy_testcase(rnd.next(EASY_RND_MIN_N, EASY_RND_MAX_N), format("11_random_%02d.in", t));
    }
    for(int t = 1; t <= 5; ++t){
        make_easy_testcase(rnd.next(EASY_MAX_N, EASY_MAX_N), format("12_max_%02d.in", t));
    }

    for(int t = 1; t <= 5; ++t){
        make_hard_testcase(rnd.next(HARD_SMALL_MIN_N, HARD_SMALL_MAX_N), format("21_small_%02d.in", t));
    }
    for(int t = 1; t <= 5; ++t){
        make_hard_testcase(rnd.next(HARD_LARGE_MIN_N, HARD_LARGE_MAX_N), format("22_large_%02d.in", t));
    }
    for(int t = 1; t <= 10; ++t){
        make_hard_testcase(rnd.next(MAX_N, MAX_N), format("23_max_%02d.in", t));
    }
    for(int t = 1; t <= 10; ++t){
        make_hard_testcase(rnd.next(MAX_N, MAX_N), format("24_tuat_%02d.in", t), "tua");
    }
    for(int t = 1; t <= 2; ++t){
        ofstream of(format("25_hand_%02d.in", t));
        of << "100000" << endl;
        int y = rnd.next(1, 99990);
        int x = 100000 - 1 - y;
        of << "t" << rnd.next("[au]{%d, %d}", x, x) << rnd.next("[t]{%d, %d}", y, y) << endl;
        of.close();
    }
    for(int t = 3; t <= 4; ++t){
        ofstream of(format("25_hand_%02d.in", t));
        of << "100000" << endl;
        int y = rnd.next(1, 99990);
        int x = 100000 - 1 - y;
        of << rnd.next("[t]{%d, %d}", y, y) << rnd.next("[au]{%d, %d}", x, x) << "t" << endl;
        of.close();
    }

    return 0;
}