// C++ Solution (Hard)

#include <iostream>
#include <vector>
using namespace std;

using ll = long long;

int main(){
    int N; cin >> N;
    vector<int> A(N);
    for(auto &a : A) cin >> a;

    vector<ll> cnt(N + 1, 0);
    ll sum = 0, ans = 0;
    for(int i = N - 1; i >= 0; --i){
        int Ai = A[i];
        ans += sum - (cnt[Ai] - 1) * cnt[Ai] / 2;
        sum += cnt[Ai];
        ++cnt[Ai];
    }
    cout << ans << endl;
}