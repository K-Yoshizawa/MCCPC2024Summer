// Solution of Hard (author : log_K)

#include <iostream>
#include <vector>
#include <array>
#include <cassert>
using namespace std;

using ll = long long;

int main(){
    cin.tie(0)->sync_with_stdio(false);
    int N; cin >> N;
    assert(N <= 2000);
    vector<int> V(N + 1);
    for(int i = 1; i <= N; ++i) cin >> V[i];
    vector<vector<int>> T(N + 1);
    for(int i = 0; i < N - 1; ++i){
        int A, B; cin >> A >> B;
        T[A].push_back(B);
        T[B].push_back(A);
    }

    vector<ll> ans(N + 1);
    // (重み, 長さ) = (0,0) (0,1) (1,0) (1,1)
    vector<int> parent_list(N + 1);
    auto rec = [&](auto self, int current, int parent, bool first = false) -> array<ll, 4> {
        if(first) parent_list[current] = parent;
        ans[current] = 0;
        array<ll, 4> ret = {};
        for(auto child : T[current]){
            if(child == parent) continue;
            auto [c00, c01, c10, c11] = self(self, child, current, first);
            ans[current] += ans[child];
            swap(c00, c01);
            swap(c10, c11);
            if(V[current] == 0){
                ans[current] += ret[0b00] * c00;
                ans[current] += ret[0b01] * c01;
                ans[current] += ret[0b10] * c10;
                ans[current] += ret[0b11] * c11;
            }
            else{
                ans[current] += ret[0b00] * c10;
                ans[current] += ret[0b01] * c11;
                ans[current] += ret[0b10] * c00;
                ans[current] += ret[0b11] * c01;
            }
            ret[0b00] += c00;
            ret[0b01] += c01;
            ret[0b10] += c10;
            ret[0b11] += c11;
        }
        if(V[current] == 0){
            ++ret[0b00];
        }
        else{
            swap(ret[0b00], ret[0b10]);
            swap(ret[0b01], ret[0b11]);
            ++ret[0b10];
        }
        ans[current] += ret[0b00];
        return ret;
    };

    auto flip = [&](auto self, int current) -> void {
        V[current] = 1 - V[current];
        for(auto child : T[current]){
            if(child == parent_list[current]) continue;
            self(self, child);
        }
        return;
    };

    // 最初の問題を解く
    {
        rec(rec, 1, 0, true);
        cout << ans[1] << endl;
    }
    // i = 1, ..., N について解く
    for(int i = 1; i <= N; ++i){
        flip(flip, i);
        rec(rec, 1, 0);
        cout << ans[1] << endl;
        flip(flip, i);
    }
}