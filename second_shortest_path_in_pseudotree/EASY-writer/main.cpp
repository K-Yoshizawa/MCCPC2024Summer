// solution of Easy (author : writer)

#include <bits/stdc++.h>
using namespace std;

int main(){
    int N; cin >> N;
    vector<vector<int>> G(N + 1);
    for(int i = 0; i < N; ++i){
        int u, v; cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    int T; cin >> T;
    int A, B; cin >> A >> B;

    assert(A == N);
    int C = G[N][1];
    if(B < C) cout << A - B << endl;
    else cout << max(B - C + 1, A - B) << endl;
}