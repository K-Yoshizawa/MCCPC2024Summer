#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main(){
    int N, M; cin >> N >> M;
    assert(N <= 50);
    vector<int> C(N); for(auto &c : C) cin >> c, --c;

    ll ans = 0;
    for(int i = 0; i < N; ++i){
        for(int j = i + 1; j < N; ++j){
            for(int k = j + 1; k < N; ++k){
                for(int l = k + 1; l < N; ++l){
                    if(C[i] == C[l] and C[i] != C[j] and C[i] != C[k] and C[j] != C[k]){
                        ++ans;
                    }
                }
            }
        }
    }
    cout << ans << endl;
}