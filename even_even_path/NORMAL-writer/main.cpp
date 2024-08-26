// Solution of Normal (author : log_K)

#include <iostream>
#include <vector>
#include <array>
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

    ll ans = 0;
    // (重み, 長さ) = (0,0) (0,1) (1,0) (1,1)
    auto dfs = [&](auto self, int current) -> array<ll, 4> {
        array<ll, 4> ret = {}, Lc = {}, Rc = {};
        int L = current * 2, R = current * 2 + 1;
        if(L <= N){
            // 左の子頂点
            Lc = self(self, L);
            // 右の子頂点
            Rc = self(self, R);
            // 子についてマージ
            swap(Lc[0b00], Lc[0b01]);
            swap(Lc[0b10], Lc[0b11]);
            swap(Rc[0b00], Rc[0b01]);
            swap(Rc[0b10], Rc[0b11]);
            if(V[current] == 0){
                for(int i = 0b00; i <= 0b11; ++i){
                    ans += Lc[i] * Rc[i];
                }
            }
            else{
                for(int i = 0b00; i <= 0b11; ++i){
                    ans += Lc[i] * Rc[i ^ 0b10];
                }
            }
            for(int i = 0b00; i <= 0b11; ++i){
                ret[i] += Lc[i] + Rc[i];
            }
        }
        // その頂点自身を追加して返す
        if(V[current] == 0){
            ++ret[0b00];
        }
        else{
            swap(ret[0b00], ret[0b10]);
            swap(ret[0b01], ret[0b11]);
            ++ret[0b10];
        }
        ans += ret[0b00];
        return ret;
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
        dfs(dfs, 1);
        cout << ans << endl;
    }
    // i = 1, ..., N について解く
    for(int i = 1; i <= N; ++i){
        flip(flip, i);
        ans = 0;
        dfs(dfs, 1);
        cout << ans << endl;
        flip(flip, i);
    }
}