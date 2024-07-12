#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main(){
    ll N, M; cin >> N >> M;
    vector<ll> P(N + 1), Q(N + 1);
    for(int i = 1; i <= N; ++i) cin >> P[i];
    for(int i = 1; i <= N; ++i) cin >> Q[i];

    int LOG = ceil(log2(M)) + 1;
    vector dat(N + 1, vector(LOG, 0LL));
    vector who(N + 1, vector(LOG, 0));
    for(int i = 1; i <= N; ++i){
        dat[i][0] = P[i];
        who[i][0] = Q[i];
    }
    for(int j = 1; j < LOG; ++j){
        for(int i = 1; i <= N; ++i){
            dat[i][j] = dat[who[i][j - 1]][j - 1] + dat[i][j - 1];
            who[i][j] = who[who[i][j - 1]][j - 1];
        }
    }

    auto search = [&](int s) -> int {
        ll step = 0;
        int ret = s;
        for(int k = LOG - 1; k >= 0; --k){
            if(step + dat[ret][k] < M){
                step += dat[ret][k];
                ret = who[ret][k];
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
    cout << ans.size() << endl;
    for(int i = 0; i < ans.size(); ++i){
        cout << ans[i] << " \n"[i == ans.size() - 1];
    }
}