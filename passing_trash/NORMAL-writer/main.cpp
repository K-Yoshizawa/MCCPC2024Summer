#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main(){
    ll N, M; cin >> N >> M;
    vector<ll> P(N + 1), Q(N + 1);
    for(int i = 1; i <= N; ++i) cin >> P[i];
    for(int i = 1; i <= N; ++i) cin >> Q[i];

    vector dat(N + 1, vector(35, 0LL));
    vector who(N + 1, vector(35, 0));
    for(int i = 1; i <= N; ++i){
        dat[i][0] = P[i];
        who[i][0] = Q[i];
    }
    for(int j = 1; j < 35; ++j){
        for(int i = 1; i <= N; ++i){
            dat[i][j] = dat[who[i][j - 1]][j - 1] + dat[i][j - 1];
            who[i][j] = who[who[i][j - 1]][j - 1];
        }
    }

    auto search = [&](int s) -> int {
        // cerr << "Start from " << s << endl;
        ll ok = 0, ng = M + 1;
        while(abs(ok - ng) > 1){
            ll md = (ok + ng) >> 1;
            ll sum = 0, rem = md;
            int now = s;
            for(int i = 0; i < 35; ++i){
                if(rem & 1){
                    sum += dat[now][i];
                    now = who[now][i];
                }
                rem >>= 1;
            }
            if(sum < M) ok = md;
            else ng = md;
        }
        int ret = s;
        ll rem = ok;
        // cerr << "Box Passes " << ok << endl;
        for(int i = 0; i < 35; ++i){
            if(rem & 1) ret = who[ret][i];
            rem >>= 1;
        }
        // cerr << "End at " << ret << endl;
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