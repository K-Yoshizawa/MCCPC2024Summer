#include <iostream>
#include <vector>
#include "testlib.h"
using namespace std;

using ll = long long;

const int MIN_N = 3;
const int MAX_N = 200000;
const ll MIN_M = 0;
const ll MAX_M = 100000000000000LL;

int main(int argc, char* argv[]){
    registerTestlibCmd(argc, argv);
    ll M = inf.readLong(MIN_M, MAX_M, "M");
    int N = ouf.readInt(MIN_N, MAX_N, "N");
    ouf.readEoln();
    vector<int> A = ouf.readInts(N, 1, N, "A");

    vector<ll> cnt(N + 1, 0);
    ll sum = 0, ans = 0;
    for(int i = N - 1; i >= 0; --i){
        int a = A[i];
        ans += sum - (cnt[a] - 1) * cnt[a] / 2;
        sum += cnt[a];
        ++cnt[a];
    }
    
    if(ans == M) quitf(_ok, "Accepted");
    else quitf(_wa, format("Expected M = %lld, but f(A) = %lld", M, ans).c_str());
}