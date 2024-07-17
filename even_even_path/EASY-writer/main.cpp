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
        for(int j = i; j <= N; j += 2){
            int weight = 0;
            for(int k = i; k <= j; ++k){
                weight += V[k];
            }
            if(weight % 2 == 0){
                ++ans;
                // cout << "i = " << i << ", j = " << j << endl;
            }
        }
    }
    cout << ans << endl;
}