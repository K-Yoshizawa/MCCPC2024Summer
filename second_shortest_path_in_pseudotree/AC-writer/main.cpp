#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <iostream>
#include <vector>
using namespace std;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int N; cin >> N;
    vector<vector<int>> G(N + 1);
    for(int i = 0; i < N; ++i){
        int u, v; cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    vector<int> leaf_vertex;
    for(int i = 1; i <= N; ++i){
        if(G[i].size() == 1) leaf_vertex.push_back(i);
    }
    int cycle_length; // サイクルに含まれる頂点数
    vector<int> depth(N + 1, -1); // 各頂点がサイクルからどれだけ離れているか (サイクル上の頂点はサイクルの中で何番目の頂点か)
    vector<int> belong(N + 1, -1); // 各頂点がどの枝に属しているか (0はサイクル)
    vector<int> reach_cycle(N + 1, -1); // 各枝がサイクル上のどの頂点につながっているか
    {
        vector<int> cycle;
        vector<bool> seen(N + 1, false), finished(N + 1, false);
        vector<int> history;
        auto dfs = [&](auto self, int current, int previous) -> int {
            seen[current] = true;
            history.push_back(current);
            for(auto adjacent : G[current]){
                if(adjacent == previous or finished[adjacent]) continue;
                if(seen[adjacent] and !finished[adjacent]){
                    history.push_back(adjacent);
                    return adjacent;
                }
                int position = self(self, adjacent, current);
                if(position != -1) return position;
            }
            finished[current] = true;
            history.pop_back();
            return -1;
        };
        int cycle_start = dfs(dfs, 1, -1);
        while(!history.empty()){
            cycle.push_back(history.back());
            history.pop_back();
            if(history.back() == cycle_start) break;
        }
        cycle_length = cycle.size();
        // reverse(cycle.begin(), cycle.end());
        for(int i = 0; i < cycle.size(); ++i){
            depth[cycle[i]] = i;
            belong[cycle[i]] = 0;
        }
    }
    {
        auto dfs = [&](auto self, int current, int previous, int current_branch) -> void {
            belong[current] = current_branch;
            for(auto adjacent : G[current]){
                if(adjacent == previous) continue;
                if(belong[adjacent] == 0){
                    reach_cycle[current_branch] = adjacent;
                    depth[current] = 1;
                    return;
                }
                self(self, adjacent, current, current_branch);
                depth[current] = depth[adjacent] + 1;
            }
            return;
        };
        for(int i = 0; i < leaf_vertex.size(); ++i){
            dfs(dfs, leaf_vertex[i], -1, i + 1);
        }
    }

    int T; cin >> T;
    while(T--){
        int A, B; cin >> A >> B;

        // 答えが存在しない場合
        // 同一枝上の頂点の場合
        if(belong[A] > 0 and belong[A] == belong[B]){
            cout << -1 << endl;
            continue;
        }
        // 片方がある枝上の頂点でもう片方がその枝が接続するサイクル上の頂点の場合
        if(min(belong[A], belong[B]) == 0 and max(belong[A], belong[B]) > 0){
            if(belong[A] > 0 and reach_cycle[belong[A]] == B or belong[B] > 0 and reach_cycle[belong[B]] == A){
                cout << -1 << endl;
                continue;
            }
        }
        // 両方が異なる枝上の頂点で、共通のサイクル上の頂点に接続する場合
        if(min(belong[A], belong[B]) > 0 and belong[A] != belong[B] and reach_cycle[belong[A]] == reach_cycle[belong[B]]){
            cout << -1 << endl;
            continue;
        }

        // そうでなければ答えが存在する
        // 両方がサイクル上の頂点の場合
        if(belong[A] == 0 and belong[B] == 0){
            cerr << "Each Vertex in Cycle" << endl;
            int dist1 = abs(depth[A] - depth[B]);
            int dist2 = cycle_length - dist1;
            cout << max(dist1, dist2) << endl;
        }
        // 片方がサイクル上の頂点の場合
        else if(min(belong[A], belong[B]) == 0){
            cerr << "Vertex in Cycle and in Branch" << endl;
            // 簡単のため A がサイクル上の頂点とする
            if(belong[B] == 0) swap(A, B);
            int C = reach_cycle[belong[B]];
            int dist1 = abs(depth[A] - depth[C]);
            int dist2 = cycle_length - dist1;
            cout << depth[B] + max(dist1, dist2) << endl;
        }
        // 両方が異なる枝上の頂点の場合
        else{
            cerr << "Each Vertex in Branch" << endl;
            int C = reach_cycle[belong[A]], D = reach_cycle[belong[B]];
            int dist1 = abs(depth[C] - depth[D]);
            int dist2 = cycle_length - dist1;
            cout << depth[A] + depth[B] + max(dist1, dist2) << endl;
        }
    }
}