#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main(){
    ll N, M; cin >> N >> M;
    vector<ll> P(N + 1), Q(N + 1);
    for(int i = 1; i <= N; ++i) cin >> P[i];
    for(int i = 1; i <= N; ++i) cin >> Q[i];

    vector<int> ans;
    for(int i = 1; i <= N; ++i){
        int now = i, rem = M;
        while(1){
            rem -= P[now];
            if(rem <= 0) break;
            now = Q[now];
        }
        ans.push_back(now);
    }
    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());
    for(int i = 0; i < ans.size(); ++i){
        cout << ans[i] << " \n"[i == ans.size() - 1];
    }
}