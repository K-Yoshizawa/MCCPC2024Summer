#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

using ll = long long;

int main(){
    ll N, M; cin >> N >> M;
    vector<ll> P(N + 1), Q(N + 1);
    for(int i = 1; i <= N; ++i) cin >> P[i];
    for(int i = 1; i <= N; ++i) cin >> Q[i];

    int LOG = min(int(ceil(log2(M))) + 1, 41);
    vector dat(LOG, vector(N + 1, 0LL));
    vector who(LOG, vector(N + 1, 0));
    for(int i = 1; i <= N; ++i){
        dat[0][i] = P[i];
        who[0][i] = Q[i];
    }
    for(int i = 1; i < LOG; ++i){
        for(int j = 1; j <= N; ++j){
            dat[i][j] = dat[i - 1][who[i - 1][j]] + dat[i - 1][j];
            who[i][j] = who[i - 1][who[i - 1][j]];
        }
    }

    auto search = [&](int s) -> int {
        ll step = 0;
        int ret = s;
        for(int k = LOG - 1; k >= 0; --k){
            if(step + dat[k][ret] < M){
                step += dat[k][ret];
                ret = who[k][ret];
            }
        }
        return ret;
    };

    vector<int> ans;
    for(int i = 1; i <= N; ++i){
        ans.push_back(search(i));
    }
    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());
    // cout << ans.size() << endl;
    for(int i = 0; i < ans.size(); ++i){
        cout << ans[i] << " \n"[i == ans.size() - 1];
    }
}