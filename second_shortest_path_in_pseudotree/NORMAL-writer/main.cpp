#include <iostream>
#include <cassert>
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
    int T; cin >> T;
    int A, B; cin >> A >> B;
    assert(T == 1);
    
    vector<bool> seen(N + 1, false);
    vector<int> ans;
    auto dfs = [&](auto self, int current, int previous, int current_distance) -> void {
        seen[current] = true;
        // cerr << "START DFS = " << current << endl;
        if(current != B){
            for(int adjacent : G[current]){
                if(adjacent == previous or seen[adjacent]) continue;
                self(self, adjacent, current, current_distance + 1);
            }
        }
        else{
            ans.push_back(current_distance);
        }
        // cerr << "END DFS = " << current << endl;
        seen[current] = false;
    };
    dfs(dfs, A, -1, 0);
    cout << (ans.size() < 2 ? -1 : max(ans[0], ans[1])) << endl;
}