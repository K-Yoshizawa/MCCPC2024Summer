#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main(){
    int N, M; cin >> N >> M;
    vector<ll> dist(N + 1, 0);
    for(int i = 0; i < M; ++i){
        int A, B, C; cin >> A >> B >> C;
        if(A == 2) dist[B] = C;
        else dist[A] = C;
    }

    int T; cin >> T;
    while(T--){
        ll K; cin >> K;
        int ans = 0;
        for(int i = 2; i <= N - 1; ++i){
            int time = max(dist[1], dist[N]) + dist[i];
            if(time <= K) ans += 1;
        }
        if(dist[1] + dist[N] <= K) ans += 2;
        cout << ans << endl;
    }
}