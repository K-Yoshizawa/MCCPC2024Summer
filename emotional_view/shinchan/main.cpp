#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define pb(a) push_back(a)
#define rep(i, n) for(int i=0;i<n;i++)
#define foa(e, v) for(auto& e : v)
using ll = long long;
const ll MOD7 = 1000000007, MOD998 = 998244353, INF = (1LL << 60);
#define dout(a) cout<<fixed<<setprecision(10)<<a<<endl;

using ld = long double;
const ld eps = 1e-9;
struct event {
    ld x, y, d;
    int id, flag, s;
};
struct query {
    int id, flag;
};
int shogen(ld x, ld y) {
    if(y >= 0) {
        if(x > 0) return 1;
        else return 2;
    } else {
        if(x >= 0) return 4;
        else return 3;
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    int n; cin >> n;
    vector<ll> x(n), y(n), r(n);
    rep(i, n) cin >> x[i] >> y[i] >> r[i];
    
    vector<event> events;
    rep(i, n) {
        ld base = atan2(y[i], x[i]);
        ld d = x[i] * x[i] + y[i] * y[i] - r[i] * r[i];
        ld len = sqrtl(d);
        ld th = acos(len / sqrt(x[i] * x[i] + y[i] * y[i]));
        {
            // ld Y = len * sin(base + th);
            // ld X = len * cos(base + th);
            ld X = len * x[i] - r[i] * y[i];
            ld Y = len * y[i] + r[i] * x[i];
            events.push_back({X, Y, d, i, 0, shogen(X, Y)});
        }{
            // ld Y = len * sin(base - th);
            // ld X = len * cos(base - th);
            ld X = len * x[i] + r[i] * y[i];
            ld Y = len * y[i] - r[i] * x[i];
            events.push_back({X, Y, d, i, 1, shogen(X, Y)});
        }
    }
    sort(all(events), [&](event a, event b) {
        if(a.s == b.s and abs(a.x * b.y - a.y * b.x) < eps) return a.flag < b.flag;
        if(a.s != b.s) return a.s < b.s;
        return a.x * b.y - a.y * b.x > 0;
    });
    vector<query> querys;
    vector<ld> dist(n);
    rep(i, n * 2) {
        auto [X, Y, d, idx, flag, s] = events[i];
        dist[idx] = d;
        querys.push_back({idx, flag});
    }
    rep(i, n * 2) querys.pb(querys[i]);
    set<ld> st;
    set<int> ans;
    int Min = -1;
    rep(i, n * 4) {
        auto [idx, flag] = querys[i];
        if(flag) {
            st.insert(dist[idx]);
            if(abs(dist[idx] - *st.begin()) < eps) Min = idx;
        } else {
            auto itr = st.lower_bound(dist[idx] - eps);
            if(itr != st.end() and *itr - dist[idx] < eps) st.erase(itr);
            if(Min == -1) continue;
            if(dist[idx] < dist[Min]) Min = -1;
            if(Min == idx) {
                if(i >= n * 2) ans.insert(idx + 1);
                Min = -1;
            }
        }
    }

    vector<int> answer;
    foa(e, ans) answer.push_back(e);
    for(int i = 0; i < answer.size(); ++i){
        cout << answer[i] << " \n"[i + 1 == answer.size()];
    }
    // foa(e, ans) cout << e << " ";
    // cout << endl;

    return 0;
}
