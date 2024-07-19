#include <bits/stdc++.h>
using namespace std;

using ll = long long;

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

    vector<ll> ans(N + 1, 0);
    vector dp(N + 1, vector(2, vector(2, ll(0))));
    auto rec = [&](auto self, int current, int parent) -> void {
        // cerr << "Vertex = " << current << " (Start)" << endl;
        ans[current] = (V[current] == 0);
        dp[current][V[current]][0] = 1;
        for(auto child : G[current]){
            if(child == parent) continue;
            self(self, child, current);
            ans[current] += ans[child];
            ans[current] += dp[child][V[current]][1];
            for(int w = 0; w < 2; ++w){
                for(int l = 0; l < 2; ++l){
                    dp[current][w][l] += dp[child][w ^ V[current]][l ^ 1];
                }
            }
        }
        if(V[current]){
            ll sum_of_even[2] = {0, 0}, sum_of_odd[2] = {0, 0}, sum_of_cross = 0;
            for(auto child : G[current]){
                if(child == parent) continue;
                for(int l = 0; l < 2; ++l){
                    sum_of_even[l] += dp[child][0][l];
                    sum_of_odd[l] += dp[child][1][l];
                    sum_of_cross += dp[child][0][l] * dp[child][1][l];
                }
            }
            ans[current] += sum_of_even[0] * sum_of_odd[0] + sum_of_even[1] * sum_of_odd[1] - sum_of_cross;
        }
        else{
            ll sum_of_square = 0;
            vector<vector<ll>> square_of_sum(2, vector<ll>(2, ll(0)));
            for(auto child : G[current]){
                if(child == parent) continue;
                for(int w = 0; w < 2; ++w){
                    for(int l = 0; l < 2; ++l){
                        sum_of_square += dp[child][w][l] * dp[child][w][l];
                        square_of_sum[w][l] += dp[child][w][l];
                    }
                }
            }
            ll tmp = 0;
            for(int w = 0; w < 2; ++w){
                for(int l = 0; l < 2; ++l){
                    square_of_sum[w][l] *= square_of_sum[w][l];
                    tmp += square_of_sum[w][l];
                }
            }
            ans[current] += (tmp - sum_of_square) / 2;
        }
        // cerr << "Vertex = " << current << " (End)" << endl;
    };
    
    rec(rec, 1, 0);
    cout << ans[1] << endl;
}