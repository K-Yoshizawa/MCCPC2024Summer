#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define pb(a) push_back(a)
#define rep(i, n) for(int i=0;i<n;i++)
#define foa(e, v) for(auto& e : v)
using ll = long long;
const ll MOD7 = 1000000007, MOD998 = 998244353, INF = (1LL << 60);
#define dout(a) cout<<fixed<<setprecision(10)<<a<<endl;

struct Doubling {
private:
    static constexpr int max_bit = 45;
    std::vector<std::array<int, max_bit>> nx;
    std::vector<std::array<ll, max_bit>> sum;
public:
    Doubling(std::vector<ll> nx_, vector<ll> a) noexcept {
        int n = nx_.size();
        nx.resize(n);
        sum.resize(n);
        for(int i = 0; i < n; i ++) nx[i][0] = nx_[i];
        for(int i = 0; i < n; i ++) sum[i][0] = a[i];
        for(int j = 0; j < max_bit - 1; j ++) for(int i = 0; i < n; i ++) {
            sum[i][j + 1] = sum[nx[i][j]][j] + sum[i][j];
            nx[i][j + 1] = nx[nx[i][j]][j];
        }
    }

    int query(int now, long long m) {
        for(int i = 44; i >= 0; i --) {
            if(m <= sum[now][i]) {
                ;
            } else {
                m -= sum[now][i];
                now = nx[now][i];
            }
        }
        return now;
        // while(m) {
        //     if(now == -1) return -1;
        //     int t = __builtin_ctzll(m);
        //     now = nx[now][t];
        //     m ^= 1LL << t;
        // }
        // return now;
    }
};


int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    ll n, m;
    cin >> n >> m;
    vector<ll> a(n), nx(n);
    rep(i, n) {
        cin >> a[i];
    }
    rep(i, n) {
        cin >> nx[i];
        nx[i] --;
    }
    set<int> ans;
    Doubling d(nx, a);
    rep(i, n) {
        ans.insert(d.query(i, m));
    }
    vector<int> answer;
    foa(e, ans) {
        // cout << e + 1 << " ";
        answer.push_back(e + 1);
    }
    // cout << endl;
    for(int i = 0; i < answer.size(); ++i){
        cout << answer[i] << " \n"[i + 1 == answer.size()];
    }
    return 0;
}
