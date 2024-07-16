#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve(){
    ll N, M, K; cin >> N >> M >> K;

    ll A = 1;
    for(int i = 0; i < M; ++i) A *= N;
    A += K;

    int ans = 0;
    while(A >= N){
        if(A % N == 0) A /= N;
        else A += (N - 1);
        ++ans;
    }
    cout << ans << endl;
}

int main(){
    int T; cin >> T;
    while(T--) solve();
}