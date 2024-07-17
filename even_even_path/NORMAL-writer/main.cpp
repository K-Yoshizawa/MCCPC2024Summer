#include <bits/stdc++.h>
using namespace std;

int main(){
    int N; cin >> N;
    vector<int> V(N + 1);
    for(int i = 1; i <= N; ++i) cin >> V[i];
    vector<vector<int>> G(N + 1);
    for(int i = 0; i < N - 1; ++i){
        int A, B; cin >> A >> B;
        G[A].push_back(B);
        G[B].push_back(A);
    }
    // int M; cin >> M;
    // vector<int> Q(M);
    // for(int i = 0; i < M; ++i) cin >> Q[i];
    
    int ans = 0;
    for(int i = 1; i <= N; ++i){
        using t = tuple<int, int, int, int>;
        queue<t> que;
        // cerr << "i = " << i << endl;
        que.emplace(i, 0, V[i], 0);
        while(que.size()){
            auto [now_vertex, prev_vertex, weight, length] = que.front();
            que.pop();
            if(weight % 2 == 0 && length % 2 == 0){
                ++ans;
                // cerr << " - count : " << now_vertex << ", " << weight << ", " << length << endl;
            }
            for(int next_vertex : G[now_vertex]){
                if(next_vertex == prev_vertex) continue;
                // cerr << " - next_vertex : " << next_vertex << endl;
                que.emplace(next_vertex, now_vertex, weight + V[next_vertex], length + 1);
            }
        }
    }
    ans += N - reduce(V.begin(), V.end());
    ans /= 2;
    cout << ans << endl;
}