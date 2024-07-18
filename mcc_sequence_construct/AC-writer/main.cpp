#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main(){
    ll M; cin >> M;
    int N = 200000;

    vector<ll> T(190001, 0);
    for(ll t = 0; t <= 190000; ++t){
        T[t] = t * (t - 1) / 2;
    }
    vector<int> where(10000, 0);
    ll remain = M;
    for(int i = 0; i < 10000; ++i){
        if(remain == 0) break;
        int v = upper_bound(T.begin(), T.end(), remain) - T.begin() - 1;
        remain -= T[v];
        where[i] = v;
    }
    vector<int> ans;
    int idx = 0;
    for(int t = 190000; t > 0; --t){
        while(idx < 10000 and t == where[idx]){
            ans.push_back(N - idx);
            ++idx;
        }
        ans.push_back(1);
    }
    while(idx < 10000){
        ans.push_back(N - idx);
        ++idx;
    }
    // for(int i = 0; i < 10000; ++i){
    //     if(where[i] > 0) cout << i << " -> " << where[i] << endl;
    // }
    cout << N << endl;
    for(int i = 0; i < ans.size(); ++i){
        cout << ans[i] << " \n"[i + 1 == N];
    }
}