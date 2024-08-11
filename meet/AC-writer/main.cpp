#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main(){
    int N, M; cin >> N >> M;
    vector<vector<pair<int, ll>>> G(N + 1);
    for(int i = 0; i < M; ++i){
        int A, B, C; cin >> A >> B >> C;
        G[A].emplace_back(B, C);
        G[B].emplace_back(A, C);
    }

    ll INF = (1LL << 60);
    vector<ll> Alice(N + 1, INF), Bob(N + 1, INF);
    using P = pair<ll, int>;
    priority_queue<P, vector<P>, greater<P>> que;
    que.emplace(0, 1);
    Alice[1] = 0;
    while(que.size()){
        auto [dist, current] = que.top();
        que.pop();
        if(Alice[current] != dist) continue;
        for(auto [adjacent, cost] : G[current]){
            ll next_dist = dist + cost;
            if(next_dist < Alice[adjacent]){
                Alice[adjacent] = next_dist;
                que.emplace(next_dist, adjacent);
            }
        }
    }
    que.emplace(0, N);
    Bob[N] = 0;
    while(que.size()){
        auto [dist, current] = que.top();
        que.pop();
        if(Bob[current] != dist) continue;
        for(auto [adjacent, cost] : G[current]){
            ll next_dist = dist + cost;
            if(next_dist < Bob[adjacent]){
                Bob[adjacent] = next_dist;
                que.emplace(next_dist, adjacent);
            }
        }
    }

    vector<ll> costs;
    for(int i = 1; i <= N; ++i){
        costs.push_back(max(Alice[i], Bob[i]));
    }
    sort(costs.begin(), costs.end());

    int T; cin >> T;
    while(T--){
        ll K; cin >> K;
        int ans = distance(costs.begin(), upper_bound(costs.begin(), costs.end(), K));
        cout << ans << endl;
    }
}