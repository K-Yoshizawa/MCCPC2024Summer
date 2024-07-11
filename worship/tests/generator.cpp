#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

tuple<int, int, int> make(int x, int y){
    int a = rnd.next(x, y);
    int b = rnd.next(x, y);
    int c = rnd.next(x, y);
    return {a, b, c};
}

int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);
    for(int t = 0; t < 5; ++t){
        ofstream of(format("01_small_%02d.in", t + 1).c_str());
        auto [a, b, c] = make(0, 10);
        of << a << " " << b << " " << c << endl;
        of.close();
    }
    for(int t = 0; t < 5; ++t){
        ofstream of(format("02_large_%02d.in", t + 1).c_str());
        auto [a, b, c] = make(800, 900);
        of << a << " " << b << " " << c << endl;
        of.close();
    }
    for(int t = 0; t < 1; ++t){
        ofstream of(format("03_max_%02d.in", t + 1).c_str());
        auto [a, b, c] = make(1000, 1000);
        of << a << " " << b << " " << c << endl;
        of.close();
    }
    {
        ofstream of(format("04_min_01.in").c_str());
        of << "1 0 0" << endl;
        of.close();
    }
    {
        ofstream of(format("04_min_02.in").c_str());
        of << "0 1 0" << endl;
        of.close();
    }
    {
        ofstream of(format("04_min_03.in").c_str());
        of << "0 0 1" << endl;
        of.close();
    }
    return 0;
}