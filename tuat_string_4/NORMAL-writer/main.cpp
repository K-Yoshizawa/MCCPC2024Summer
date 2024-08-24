#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template< int mod >
struct ModInt {
    int x;

    ModInt() : x(0) {}

    ModInt(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}

    ModInt &operator+=(const ModInt &p) {
        if((x += p.x) >= mod) x -= mod;
        return *this;
    }

    ModInt &operator-=(const ModInt &p) {
        if((x += mod - p.x) >= mod) x -= mod;
        return *this;
    }

    ModInt &operator*=(const ModInt &p) {
        x = (int) (1LL * x * p.x % mod);
        return *this;
    }

    ModInt &operator/=(const ModInt &p) {
        *this *= p.inverse();
        return *this;
    }

    ModInt operator-() const { return ModInt(-x); }

    ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }

    ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }

    ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }

    ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }

    bool operator==(const ModInt &p) const { return x == p.x; }

    bool operator!=(const ModInt &p) const { return x != p.x; }

    ModInt inverse() const {
        int a = x, b = mod, u = 1, v = 0, t;
        while(b > 0) {
            t = a / b;
            swap(a -= t * b, b);
            swap(u -= t * v, v);
        }
        return ModInt(u);
    }

    ModInt pow(int64_t n) const {
        ModInt ret(1), mul(x);
        while(n > 0) {
            if(n & 1) ret *= mul;
            mul *= mul;
            n >>= 1;
        }
        return ret;
    }

    friend ostream &operator<<(ostream &os, const ModInt &p) {
        return os << p.x;
    }

    friend istream &operator>>(istream &is, ModInt &a) {
        int64_t t;
        is >> t;
        a = ModInt< mod >(t);
        return (is);
    }

    static int get_mod() { return mod; }
};

using mint = ModInt< 998244353 >;

int main(){
    int N, M; cin >> N >> M;
    vector<int> C(N); for(auto &c : C) cin >> c, --c;
    
    vector<vector<int>> where(M);
    vector<vector<ll>> freq(M, vector<ll>(N, 0));
    for(int i = 0; i < N; ++i){
        ++freq[C[i]][i];
        where[C[i]].push_back(i);
    }
    for(int c = 0; c < M; ++c){
        for(int i = 1; i < N; ++i){
            freq[c][i] += freq[c][i - 1];
        }
    }

    auto f = [&](char c, int i, int j){
        return mint(freq[c][j] - freq[c][i]);
    };

    mint ans = 0;
    for(int i = 0; i < N; ++i){
        int ci = C[i];
        for(int j = i + 1; j < N; ++j){
            int cj = C[j];
            if(ci != cj) continue;
            vector<mint> cnt(M, 0);
            for(int c = 0; c < M; ++c){
                if(c == ci) continue;
                cnt[c] = f(c, i, j);
            }
            for(int c = 0; c < M; ++c){
                for(int d = c + 1; d < M; ++d){
                    ans += cnt[c] * cnt[d];
                }
            }
        }
    }
    cout << ans << endl;
}