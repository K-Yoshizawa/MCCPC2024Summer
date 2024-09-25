#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define pb(a) push_back(a)
#define rep(i, n) for(int i=0;i<n;i++)
#define foa(e, v) for(auto& e : v)
using ll = long long;
const ll MOD7 = 1000000007, MOD998 = 998244353, INF = (1LL << 60);
#define dout(a) cout<<fixed<<setprecision(10)<<a<<endl;

template<int MOD> struct Modint {
    long long val;
    constexpr Modint(long long v = 0) noexcept : val(v % MOD) { if (val < 0) val += MOD; }
    constexpr int mod() const { return MOD; }
    constexpr long long value() const { return val; }
    constexpr Modint operator - () const noexcept { return val ? MOD - val : 0; }
    constexpr Modint operator + (const Modint& r) const noexcept { return Modint(*this) += r; }
    constexpr Modint operator - (const Modint& r) const noexcept { return Modint(*this) -= r; }
    constexpr Modint operator * (const Modint& r) const noexcept { return Modint(*this) *= r; }
    constexpr Modint operator / (const Modint& r) const noexcept { return Modint(*this) /= r; }
    constexpr Modint& operator += (const Modint& r) noexcept {
        val += r.val;
        if (val >= MOD) val -= MOD;
        return *this;
    }
    constexpr Modint& operator -= (const Modint& r) noexcept {
        val -= r.val;
        if (val < 0) val += MOD;
        return *this;
    }
    constexpr Modint& operator *= (const Modint& r) noexcept {
        val = val * r.val % MOD;
        return *this;
    }
    constexpr Modint& operator /= (const Modint& r) noexcept {
        long long a = r.val, b = MOD, u = 1, v = 0;
        while (b) {
            long long t = a / b;
            a -= t * b, swap(a, b);
            u -= t * v, swap(u, v);
        }
        val = val * u % MOD;
        if (val < 0) val += MOD;
        return *this;
    }
    constexpr bool operator == (const Modint& r) const noexcept { return this->val == r.val; }
    constexpr bool operator != (const Modint& r) const noexcept { return this->val != r.val; }
    friend constexpr istream& operator >> (istream& is, Modint<MOD>& x) noexcept {
        is >> x.val;
        x.val %= MOD;
        if (x.val < 0) x.val += MOD;
        return is;
    }
    friend constexpr ostream& operator << (ostream& os, const Modint<MOD>& x) noexcept {
        return os << x.val;
    }
    constexpr Modint<MOD> pow(long long n) noexcept {
        if (n == 0) return 1;
        if (n < 0) return this->pow(-n).inv();
        Modint<MOD> ret = pow(n >> 1);
        ret *= ret;
        if (n & 1) ret *= *this;
        return ret;
    }
    constexpr Modint<MOD> inv() const noexcept {
        long long a = this->val, b = MOD, u = 1, v = 0;
        while (b) {
            long long t = a / b;
            a -= t * b, swap(a, b);
            u -= t * v, swap(u, v);
        }
        return Modint<MOD>(u);
    }
};

const int MOD = MOD998;
using mint = Modint<MOD>;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    ll n, m;
    cin >> n >> m;

    mint ans = 0;
    vector<ll> a(n);
    vector<vector<ll>> v(m);
    rep(i, n) {
        cin >> a[i];
        a[i] --;
        v[a[i]].pb(i);
    }
    for(ll x = 0; x < m; x ++) {
        ll sz = v[x].size();
        for(ll i = 0; i < sz - 1; i ++) {
            ll I = v[x][i];
            vector<ll> cnt(m, 0LL);
            ll idx = i + 1;
            for(ll j = I + 1; j < n; j ++) {
                if(v[x][idx] <= j) idx ++;
                if(idx == sz) break;
                cnt[a[j]] ++;
                if(a[j] == x) continue;
                ans += mint(j - I - cnt[x] - cnt[a[j]]) * mint(sz - idx);
            }
        }
    }
    cout << ans << endl;
    return 0;
}
