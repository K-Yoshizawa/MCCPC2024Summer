#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <cassert>

using std::cerr;
using std::cin;
using std::cout;
using std::pair;
using std::string;
using std::vector;
using ll = long long;

#define rep(i, n) for (int i = 0; i < (n); ++i)


void bottom2(ll num) {
    printf("%02lld", num % 100);
}

int main() {
    int N; string Ms;
    cin >> N >> Ms;

    int M = stoi(
            Ms.substr(
                    std::max(
                            0,
                            int(Ms.size()) - 3
                    ))) % 100;


    rep(i, N) {
        rep(j, N) {
            if (j > 0) printf(" ");
            bottom2(ll(M + i) * (M + j));
        }
        printf("\n");
    }

    return 0;
}
