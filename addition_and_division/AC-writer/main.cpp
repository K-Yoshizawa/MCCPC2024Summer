#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve(){
    ll N, M, K; cin >> N >> M >> K;
    
    cout << M * (K + 1) + (K + 1) / N << endl;
}

int main(){
    int T; cin >> T;
    while(T--) solve();
}