// Solution of Easy (author : log_K)

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <cassert>
#include <bit>
using namespace std;

using ll = long long;

int main(){
    cin.tie(0)->sync_with_stdio(false);
    int N; cin >> N;
    assert(N <= 1023);
    assert(popcount((unsigned int)(N + 1)) == 1);
    vector<int> V(N + 1);
    for(int i = 1; i <= N; ++i) cin >> V[i];
    vector<vector<int>> T(N + 1);
    for(int i = 1; i <= N - 1; ++i){
        int A, B; cin >> A >> B;
        assert(A == (i + 1) / 2);
        assert(B == i + 1);
        T[A].push_back(B);
        T[B].push_back(A);
    }

    auto f = [&]() -> int {
        int ret = 0;
        for(int u = 1; u <= N; ++u){
            queue<tuple<int, int, int, int>> que;
            que.emplace(u, 0, V[u], 0);
            while(que.size()){
                auto [v, pre, weight, length] = que.front();
                que.pop();
                if(weight % 2 == 0 && length % 2 == 0){
                    ++ret;
                    if(v == u) ++ret;
                }
                int L = v * 2, R = v * 2 + 1, P = v / 2;
                if(L <= N){
                    if(L != pre) que.emplace(L, v, weight + V[L], length + 1);
                    if(R != pre) que.emplace(R, v, weight + V[R], length + 1);
                }
                if(P >= 1 && P != pre) que.emplace(P, v, weight + V[P], length + 1);
            }
        }
        return ret / 2;
    };

    auto flip = [&](auto self, int current) -> void {
        V[current] = 1 - V[current];
        int L = current * 2, R = current * 2 + 1;
        if(L <= N){
            self(self, L);
            self(self, R);
        }
        return;
    };

    // 最初の問題を解く
    {
        cout << f() << endl;
    }
    // i = 1, ..., N について解く
    for(int i = 1; i <= N; ++i){
        flip(flip, i);
        cout << f() << endl;
        flip(flip, i);
    }
}