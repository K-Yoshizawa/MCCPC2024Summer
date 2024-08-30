#include <bits/stdc++.h>
#include "testlib.h"
#include "constrains.h"
using namespace std;

void make_sample_testcase(){
    {
        ofstream of("00_sample_01.in");
        of << "123+456" << endl;
        of.close();
    }
    {
        ofstream of("00_sample_02.in");
        of << "G(4096)" << endl;
        of.close();
    }
    {
        ofstream of("00_sample_03.in");
        of << "H(4096)" << endl;
        of.close();
    }
    {
        ofstream of("00_sample_04.in");
        of << "G(0000)+H(0000)" << endl;
        of.close();
    }
    {
        ofstream of("00_sample_05.in");
        of << "H(G(12345678901234567890))" << endl;
        of.close();
    }
    {
        ofstream of("00_sample_06.in");
        of << "G(H(57))+H(628+222)+H(H(197203))" << endl;
        of.close();
    }
    {
        ofstream of("00_sample_07.in");
        of << "G(998+H(244)+G(353))+H(3+G(H(14+G(15))+92)+65+G(3))" << endl;
        of.close();
    }
}

string expr(int remain, int only, int connect);
string term(int remain, int is_number, int is_grow, int is_heavest);
string number(int remain);

string expr(int remain, int only = 0, int connect = 50){
    if(remain <= 2) connect = 0;
    string ret;
    int sub = 0;
    if(rnd.next(1, only + connect) > only){
        sub = rnd.next(2, remain - 1);
    }
    ret += term(remain - sub, only, connect / 2, connect / 2);
    if(sub > 0){
        ret += "+" + expr(sub - 1, only + 1, connect - 1);
    }
    return ret;
}

string term(int remain, int is_number = 1, int is_grow = 2, int is_heavest = 2){
    string ret;
    if(remain < 4) is_grow = is_heavest = 0;
    if(remain > 1000) is_number = 0;
    int p = rnd.next(1, is_number + is_grow + is_heavest);
    if(p <= is_number){
        ret += number(remain);
    }
    else if(p <= is_number + is_grow){
        ret += "G(" + expr(remain - 3, is_number + 1, 50 - (is_number + 1)) + ")";
    }
    else{
        ret += "H(" + expr(remain - 3, is_number + 1, 50 - (is_number + 1)) + ")";
    }
    return ret;
}

string number(int remain){
    return rnd.next(format("[0-9]{%d, %d}", remain, remain));
}

string simple(int mode, int N){
    if(mode == 0){
        int X = rnd.next(1, N - 2);
        int Y = N - 1 - X;
        return number(X) + "+" + number(Y);
    }
    return string(mode == 1 ? "G" : "H") + "(" + number(N - 3) + ")";
}

void make_dataset1(int testcase_size){
    for(int t = 1; t <= testcase_size; ++t){
        ofstream of(format("10_random_%02d.in", t));
        of << simple(0, rnd.next(3, 20)) << endl;
        of.close();
    }
    for(int t = testcase_size + 1; t <= 2 * testcase_size; ++t){
        ofstream of(format("10_random_%02d.in", t));
        of << simple(0, rnd.next(100, 200)) << endl;
        of.close();
    }
}

void make_dataset2(int testcase_size){
    for(int t = 1; t <= testcase_size; ++t){
        int N = rnd.next(5, 10);
        ofstream of(format("20_random_%02d.in", t));
        of << simple(1, N) << endl;
        of.close();
    }
    for(int t = testcase_size + 1; t <= 2 * testcase_size; ++t){
        int N = rnd.next(100, 200);
        ofstream of(format("20_random_%02d.in", t));
        of << simple(1, N) << endl;
        of.close();
    }
}

void make_dataset3(int testcase_size){
    for(int t = 1; t <= testcase_size; ++t){
        int N = rnd.next(5, 10);
        ofstream of(format("30_random_%02d.in", t));
        of << simple(2, N) << endl;
        of.close();
    }
    for(int t = testcase_size + 1; t <= 2 * testcase_size; ++t){
        int N = rnd.next(100, 200);
        ofstream of(format("30_random_%02d.in", t));
        of << simple(2, N) << endl;
        of.close();
    }
}

void make_dataset4(int testcase_size){
    for(int t = 1; t <= testcase_size; ++t){
        int X = rnd.next(20, 200);
        int Y = rnd.next(20, 200);
        ofstream of(format("40_random_%02d.in", t));
        of << simple(rnd.next(1, 2), X) << "+" << simple(rnd.next(1, 2), Y) << endl;
        of.close();
    }
}

void make_dataset5(int testcase_size){
    for(int t = 1; t <= testcase_size; ++t){
        int N = rnd.next(3, 10);
        ofstream of(format("50_random_%02d.in", t));
        of << simple(rnd.next(1, 2), rnd.next(20, 200));
        for(int i = 1; i < N; ++i){
            of << "+" << simple(rnd.next(1, 2), rnd.next(20, 200));
        }
        of << endl;
        of.close();
    }
}

void make_dataset6(int testcase_size){
    for(int t = 1; t <= testcase_size; ++t){
        ofstream of(format("60_random_%02d.in", t));
        of << string(rnd.next(0, 1) ? "G(" : "H(") + simple(rnd.next(0, 2), rnd.next(10, 30)) + ")" << endl;
        of.close();
    }
}

void make_dataset7(int testcase_size){
    for(int t = 1; t <= testcase_size; ++t){
        ofstream of(format("70_random_%02d.in", t));
        of << string(rnd.next(0, 1) ? "G(" : "H(") + simple(rnd.next(0, 2), rnd.next(10, 30)) + ")";
        int N = rnd.next(1, 9);
        for(int i = 0; i < N; ++i){
            of << "+" + string(rnd.next(0, 1) ? "G(" : "H(") + simple(rnd.next(0, 2), rnd.next(10, 30)) + ")";
        }
        of << endl;
        of.close();
    }
}

void make_hard_testcase(int N, string case_name){
    string S = expr(N);
    ofstream of(case_name.c_str());
    of << S << endl;
    of.close();
    return;
}

int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);

    make_sample_testcase();
    make_dataset1(5);
    make_dataset2(5);
    make_dataset3(5);
    make_dataset4(10);
    make_dataset5(10);
    make_dataset6(10);
    make_dataset7(10);

    for(int t = 1; t <= 5; ++t){
        make_hard_testcase(rnd.next(400000, 450000), format("80_random_%02d.in", t));
    }
    for(int t = 6; t <= 10; ++t){
        make_hard_testcase(500000, format("80_random_%02d.in", t));
    }
    {
        ofstream of(format("81_hand_01.in").c_str());
        for(int i = 0; i < 166333; ++i) of << "G(";
        for(int i = 0; i < 1000; ++i) of << "0";
        for(int i = 0; i < 166333; ++i) of << ")";
        of << endl;
        of.close();
    }
    {
        ofstream of(format("81_hand_02.in").c_str());
        for(int i = 0; i < 166333; ++i) of << "H(";
        for(int i = 0; i < 1000; ++i) of << rnd.next(0, 9);
        for(int i = 0; i < 166333; ++i) of << ")";
        of << endl;
        of.close();
    }
    {
        ofstream of(format("81_hand_03.in").c_str());
        for(int i = 0; i < 166333; ++i) of << rnd.next("[GH]") << "(";
        for(int i = 0; i < 1000; ++i) of << rnd.next(0, 9);
        for(int i = 0; i < 166333; ++i) of << ")";
        of << endl;
        of.close();
    }

    return 0;
}