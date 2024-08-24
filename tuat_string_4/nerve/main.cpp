// author : Nerve

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using vl = vector<ll>;
template<class T> using vc = vector<T>;
template<class T> using vvc = vector<vector<T>>;

#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define rep(i, n) for (ll i = 0; i < (n); i++)
#define repr(i, n) for (ll i = (n)-1; i >= 0; i--)
#define repe(i, l, r) for (ll i = (l); i < (r); i++)
#define reper(i, l, r) for (ll i = (r)-1; i >= (l); i--)
#define repa(i,n) for (auto& i: n)

template<class T1, class T2> inline bool chmax(T1 &a, const T2 &b) {if (a<b) { a=b; return 1;} return 0;}
template<class T1, class T2> inline bool chmin(T1 &a, const T2 &b) {if (b<a) { a=b; return 1;} return 0;}

struct init{init(){cin.tie(0);ios::sync_with_stdio(false);cout<<fixed<<setprecision(15);cerr<<fixed<<setprecision(15);}}init_;

template <typename T, typename U> ostream& operator<<(ostream&out,const pair<T, U>&a){return out<<a.first<<' '<<a.second;}
template <typename T> ostream& operator<<(ostream&out, const vector<T>&a){for(auto it=a.begin();it!= a.end();){out<<*it;if(++it!=a.end())out<<' ';}return out;}
template <typename T, size_t N> ostream& operator<<(ostream&out, const array<T, N>&a){for(auto it=a.begin();it!= a.end();){out<<*it;if(++it!=a.end())out<<' ';}return out;}
template <typename T> ostream& operator<<(ostream&out, const set<T>&a){for(auto it=a.begin();it!=a.end();){out<<*it;if(++it!=a.end())out<<' ';}return out;}
template <typename T, typename U> ostream& operator<<(ostream&out, const map<T, U>&a){for(auto it=a.begin();it!=a.end();){out<<*it;if(++it!=a.end())out<<'\n';}return out;}

#ifdef DEBUG
template <class T, class N> void verr(const vector<T>& a, const N& n) { rep(i, n) cerr << a[i] << " "; cerr << endl; }
template <class T, class N, size_t AN> void verr(const array<T, AN>& a, const N& n) { rep(i, n) cerr << a[i] << " "; cerr << endl; }
ll dbgt = 1; void err() { cerr << "passed " << dbgt++ << endl; }
template<class H, class... T> void err(H&& h,T&&... t){ cerr<< h << (sizeof...(t)?" ":"\n") << flush; if(sizeof...(t)>0) err(forward<T>(t)...); }
#else
void err(){}
template <class H, class... T>
void err(H &&h, T &&...t) {}
template <class H, class... T>
void verr(H &&h, T &&...t) {}
#endif

const ll INF = 4e18;
const ld EPS = 1e-11;
const ld PI = acos(-1.0L);
// const ll MOD = 1e9 + 7;
const ll MOD = 998244353;
//--------------------------------------------------------------------------------//
// modint
template <int _MOD>
struct modint {
    long long val;
    static const int mod = _MOD;
    modint(long long v = 0) noexcept : val(v % mod) {
        if (val < 0) val += mod;
    }
    inline modint operator-() const noexcept {
        return val ? mod - val : 0;
    }
    inline modint operator+(const modint &r) const noexcept { return modint(*this) += r; }
    inline modint operator-(const modint &r) const noexcept { return modint(*this) -= r; }
    inline modint operator*(const modint &r) const noexcept { return modint(*this) *= r; }
    inline modint operator/(const modint &r) const noexcept { return modint(*this) /= r; }
    inline modint &operator+=(const modint &r) noexcept {
        val += r.val;
        if (val >= mod) val -= mod;
        return *this;
    }
    inline modint &operator-=(const modint &r) noexcept {
        val -= r.val;
        if (val < 0) val += mod;
        return *this;
    }
    inline modint &operator*=(const modint &r) noexcept {
        val = val * r.val % mod;
        return *this;
    }
    inline modint &operator/=(const modint &r) noexcept {
        long long a = r.val, b = mod, u = 1, v = 0;
        while (b) {
            long long t = a / b;
            a -= t * b;
            swap(a, b);
            u -= t * v;
            swap(u, v);
        }
        val = val * u % mod;
        if (val < 0) val += mod;
        return *this;
    }
    inline bool operator==(const modint &r) const noexcept {
        return this->val == r.val;
    }
    inline bool operator!=(const modint &r) const noexcept {
        return this->val != r.val;
    }
    inline friend ostream &operator<<(ostream &os, const modint &x) noexcept {
        return os << x.val;
    }
    inline friend istream &operator>>(istream &is, modint &x) noexcept {
        is >> x.val;
        x = modint(x.val);
        return is;
    }
    inline friend modint modpow(const modint &a, long long n) noexcept {
        modint t = 1, v = a;
        while (n) {
            if (n & 1) t *= v;
            v *= v;
            n >>= 1;
        }
        return t;
    }
    inline friend modint modinv(const modint &a) noexcept {
        return modpow(a, mod - 2);
    }
};
using mint = modint<MOD>;

constexpr int MAX_M = 1000;

// (S_i, S_j) を数える
mint counts[MAX_M][MAX_M];

int main() {
    int N, M;
    cin >> N >> M;
    vc<int> C(N);
    rep(i, N) cin >> C[i], C[i]--;

    vc<mint> left_sum(M);
    rep(i, N) {
        rep(j, M) {
            if (C[i] == j) continue;
            counts[j][C[i]] += left_sum[j];
        }
        left_sum[C[i]] += 1;
    }

    mint ans = 0;
    vc<mint> right_sum(M);

    vc<mint> allsum(M);
    rep(i, M) rep(j, M) allsum[i] += counts[i][j];

    // S_kを見て数える
    repr(i, N) {
        rep(j, M) {
            if (C[i] == j) continue;
            ans += (allsum[j] - counts[j][C[i]]) * right_sum[j];
        }

        right_sum[C[i]] += 1;

        rep(j, M) {
            if (C[i] == j) continue;
            counts[j][C[i]] -= left_sum[j];
            allsum[j] -= left_sum[j];
        }

        left_sum[C[i]] -= 1;
    }

    cout << ans << endl;
}