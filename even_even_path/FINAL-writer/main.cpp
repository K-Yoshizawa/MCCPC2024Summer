// Solution of Final (author : log_K)

#include <iostream>
#include <vector>
#include <array>
using namespace std;

using ll = long long;

int main(){
    cin.tie(0)->sync_with_stdio(false);
    int N; cin >> N;
    vector<int> V(N + 1);
    for(int i = 1; i <= N; ++i) cin >> V[i];
    vector<vector<int>> T(N + 1);
    for(int i = 0; i < N - 1; ++i){
        int A, B; cin >> A >> B;
        T[A].push_back(B);
        T[B].push_back(A);
    }

    vector<ll> ans(N + 1), sub_ans(N + 1);
    // totori さんのをパクる
    // (重み, 長さ) = (0,0) (0,1) (1,0) (1,1)
    vector<int> parent_list(N + 1);
    vector<array<ll, 4>> matrix(N + 1);
    auto dfs1 = [&](auto self, int current, int parent, bool first = false) -> array<ll, 4> {
        if(first){
            parent_list[current] = parent;
            // fprintf(stderr, "# Vertex %d (start)\n", current);
        }
        ans[current] = sub_ans[current] = 0;
        array<ll, 4> ret = {};
        for(auto child : T[current]){
            if(child == parent) continue;
            auto [c00, c01, c10, c11] = self(self, child, current, first);
            ans[current] += ans[child];
            sub_ans[current] += sub_ans[child];
            swap(c00, c01);
            swap(c10, c11);
            // if(first){
            //     fprintf(stderr, "# Child Vertex %d of Vertex %d -> [%lld], <%lld>\n", child, current, ans[current], sub_ans[current]);
            //     fprintf(stderr, "    [%2lld, %2lld]\n", ret[0b00], ret[0b01]);
            //     fprintf(stderr, "    [%2lld, %2lld]\n", ret[0b10], ret[0b11]);
            //     fprintf(stderr, "    [%2lld, %2lld]\n", c00, c01);
            //     fprintf(stderr, "    [%2lld, %2lld]\n", c10, c11);
            // }
            if(V[current] == 0){
                ans[current] += ret[0b00] * c00;
                ans[current] += ret[0b01] * c01;
                ans[current] += ret[0b10] * c10;
                ans[current] += ret[0b11] * c11;
                sub_ans[current] += ret[0b00] * c10;
                sub_ans[current] += ret[0b01] * c11;
                sub_ans[current] += ret[0b10] * c00;
                sub_ans[current] += ret[0b11] * c01;
            }
            else{
                ans[current] += ret[0b00] * c10;
                ans[current] += ret[0b01] * c11;
                ans[current] += ret[0b10] * c00;
                ans[current] += ret[0b11] * c01;
                sub_ans[current] += ret[0b00] * c00;
                sub_ans[current] += ret[0b01] * c01;
                sub_ans[current] += ret[0b10] * c10;
                sub_ans[current] += ret[0b11] * c11;
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
        sub_ans[current] += ret[0b10];
        // if(first){
        //     fprintf(stderr, "# Vertex %d -> [%lld], <%lld>\n", current, ans[current], sub_ans[current]);
        //     fprintf(stderr, "    [%2lld, %2lld]\n", ret[0b00], ret[0b01]);
        //     fprintf(stderr, "    [%2lld, %2lld]\n", ret[0b10], ret[0b11]);
        // }
        return matrix[current] = ret;
    };

    auto dfs2 = [&](auto self, int current, int parent, array<ll, 4> offset) -> void {
        // {
        //     fprintf(stderr, "# Vertex %d -> [%lld], <%lld>\n", current, ans[current], sub_ans[current]);
        //     fprintf(stderr, "    [%2lld, %2lld]\n", offset[0b00], offset[0b01]);
        //     fprintf(stderr, "    [%2lld, %2lld]\n", offset[0b10], offset[0b11]);
        // }
        ans[current] = ans[0] - ans[current] + sub_ans[current];
        ans[current] -= matrix[current][0b00] * offset[0b00];
        ans[current] -= matrix[current][0b10] * offset[0b10];
        ans[current] += matrix[current][0b00] * offset[0b10];
        ans[current] += matrix[current][0b10] * offset[0b00];
        for(auto child : T[current]){
            if(child == parent) continue;
            auto next_offset = offset;
            auto [p00, p01, p10, p11] = matrix[current];
            auto [c00, c01, c10, c11] = matrix[child];
            swap(c00, c01);
            swap(c10, c11);
            if(V[current] == 1){
                swap(next_offset[0b00], next_offset[0b10]);
                swap(next_offset[0b01], next_offset[0b11]);
                swap(c00, c10);
                swap(c01, c11);
            }
            p00 -= c00, p01 -= c01, p10 -= c10, p11 -= c11;
            next_offset[0b00] += p00;
            next_offset[0b01] += p01;
            next_offset[0b10] += p10;
            next_offset[0b11] += p11;
            swap(next_offset[0b00], next_offset[0b01]);
            swap(next_offset[0b10], next_offset[0b11]);
            self(self, child, current, next_offset);
        }
        return;
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
        dfs1(dfs1, 1, 0, true);
        ans[0] = ans[1];
    }
    // i = 1, ..., N について解く
    array<ll, 4> init = {};
    dfs2(dfs2, 1, 0, init);
    for(int i = 0; i <= N; ++i){
        cout << ans[i] << endl;
    }
}