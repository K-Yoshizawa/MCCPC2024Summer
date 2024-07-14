#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main(){
    int N; cin >> N;
    vector<int> A(N);
    for(auto &a : A) cin >> a;

    vector<ll> cnt(N + 1, 0);
    ll sum = 0, ans = 0;
    for(int i = N - 1; i >= 0; --i){
        int a = A[i];
        ans += sum - (cnt[a] - 1) * cnt[a] / 2;
        sum += cnt[a];
        ++cnt[a];
    }
    cout << ans << endl;
}