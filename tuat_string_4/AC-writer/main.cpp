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
    // string S; cin >> S;
    vector<int> C(N);
    for(auto &c : C) cin >> c, --c;
    
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

    auto f = [&](int c, int i, int j){
        return mint(freq[c][j] - freq[c][i]);
    };

    mint ans = 0;
    for(int c = 0; c < M; ++c){
        // bool print_flag_c = (c + 'a' == 't' or c + 'a' == 'u' or c + 'a' == 'a');
        // if(print_flag_c) cerr << "c = " << (char)('a' + c) << endl;
        int x = where[c].size();
        vector<mint> sum(M, 0);
        vector<vector<mint>> left_cum(M, vector<mint>(x, 0));
        vector<vector<mint>> right_cum(M, vector<mint>(x, 0));
        vector<mint> left_cum_sum(x, 0);
        vector<mint> right_cum_sum(x, 0);
        for(int c1 = 0; c1 < M; ++c1){
            // bool print_flag_c1 = (c1 + 'a' == 't' or c1 + 'a' == 'u' or c1 + 'a' == 'a');
            for(int i = 0; i < x - 1; ++i){
                int l = where[c][i], r = where[c][i + 1] - 1;
                sum[c1] += f(c1, l, r) * (i + 1) * (x - i - 1);
                left_cum[c1][i] = right_cum[c1][i] = f(c1, l, r);
            }
            // if(print_flag_c and print_flag_c1){
            //     cerr << " - " << (char)('a' + c1) << " sum : " << sum[c1] << endl;
            //     cerr << " - " << (char)('a' + c1) << " freq : ";
            //     for(int i = 0; i < x - 1; ++i) cerr << left_cum[c1][i] << " ";
            //     cerr << endl;
            // }
            for(int i = 1; i < x; ++i){
                left_cum[c1][i] += left_cum[c1][i - 1];
            }
            for(int i = x - 2; i >= 0; --i){
                right_cum[c1][i] += right_cum[c1][i + 1];
            }
            for(int i = 1; i < x; ++i){
                left_cum[c1][i] += left_cum[c1][i - 1];
            }
            for(int i = x - 2; i >= 0; --i){
                right_cum[c1][i] += right_cum[c1][i + 1];
            }
            for(int i = 0; i < x; ++i){
                left_cum_sum[i] += left_cum[c1][i];
                right_cum_sum[i] += right_cum[c1][i];
            }
            // if(print_flag_c and print_flag_c1){
            //     cerr << " - " << (char)('a' + c1) << " left_cum : ";
            //     for(int i = 0; i < x - 1; ++i) cerr << left_cum[c1][i] << " ";
            //     cerr << endl;
            //     cerr << " - " << (char)('a' + c1) << " right_cum : ";
            //     for(int i = 0; i < x - 1; ++i) cerr << right_cum[c1][i] << " ";
            //     cerr << endl;
            // }
        }
        mint all_sum = reduce(sum.begin(), sum.end());
        // if(print_flag_c) cerr << " - all_sum = " << all_sum << endl;
        for(int c1 = 0; c1 < M; ++c1){
            // bool print_flag_c1 = (c1 + 'a' == 't' or c1 + 'a' == 'u' or c1 + 'a' == 'a');
            mint sub_sum = all_sum - sum[c1];
            // if(print_flag_c and print_flag_c1) cerr << " - c1 = " << (char)('a' + c1) << ", sub_sum = " << sub_sum << endl;
            for(int i = 0; i < x - 1; ++i){
                int l = where[c][i], r = where[c][i + 1] - 1;
                mint tmp_sum = sub_sum;
                if(i > 0) tmp_sum += left_cum[c1][i - 1] * (x - i - 1) - left_cum_sum[i - 1] * (x - i - 1);
                tmp_sum += right_cum[c1][i + 1] * (i + 1);
                tmp_sum -= right_cum_sum[i + 1] * (i + 1);
                // for(int c2 = 0; c2 < M; ++c2){
                //     if(c1 == c2) continue;
                //     tmp_sum -= left_cum[c2][i - 1] * (x - i - 1) + right_cum[c2][i + 1] * (i + 1);
                // }
                // if(print_flag_c and print_flag_c1){
                //     cerr << " -  - i = " << i << " -> " << f(c1, l, r) << " * " << tmp_sum << endl;
                // }
                ans += f(c1, l, r) * tmp_sum;
            }
        }
    }
    cout << ans / 2 << endl;
}