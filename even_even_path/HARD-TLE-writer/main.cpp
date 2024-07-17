#include <bits/stdc++.h>
using namespace std;

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
    int N; cin >> N;
    vector<int> V(N + 1);
    for(int i = 1; i <= N; ++i) cin >> V[i];
    vector<vector<int>> G(N + 1);
    for(int i = 0; i < N - 1; ++i){
        int A, B; cin >> A >> B;
        G[A].push_back(B);
        G[B].push_back(A);
    }
    // int M; cin >> M;
    // vector<int> Q(M);
    // for(int i = 0; i < M; ++i) cin >> Q[i];

    vector<mint> ans(N + 1, 0);
    vector dp(N + 1, vector(2, vector(2, mint(0))));
    auto rec = [&](auto self, int current, int parent) -> void {
        // cerr << "Vertex = " << current << " (Start)" << endl;
        ans[current] = (V[current] == 0);
        dp[current][V[current]][0] = 1;
        for(auto child : G[current]){
            if(child == parent) continue;
            self(self, child, current);
            ans[current] += ans[child];
            ans[current] += dp[child][V[current]][1];
            for(int w = 0; w < 2; ++w){
                for(int l = 0; l < 2; ++l){
                    dp[current][w][l] += dp[child][w ^ V[current]][l ^ 1];
                }
            }
        }
        if(V[current]){
            // mint sum_of_even[2] = {0, 0}, sum_of_odd[2] = {0, 0}, sum_of_cross = 0;
            // for(auto child : G[current]){
            //     if(child == parent) continue;
            //     for(int l = 0; l < 2; ++l){
            //         sum_of_even[l] += dp[child][0][l];
            //         sum_of_odd[l] += dp[child][1][l];
            //         sum_of_cross += dp[child][0][l] * dp[child][1][l];
            //     }
            // }
            // ans[current] += sum_of_even[0] * sum_of_odd[0] + sum_of_even[1] * sum_of_odd[1] - sum_of_cross;
            for(int i = 0; i < G[current].size(); ++i){
                if(G[current][i] == parent) continue;
                for(int j = i + 1; j < G[current].size(); ++j){
                    if(G[current][j] == parent) continue;
                    ans[current] += dp[G[current][i]][0][0] * dp[G[current][j]][1][0];
                    ans[current] += dp[G[current][i]][1][0] * dp[G[current][j]][0][0];
                    ans[current] += dp[G[current][i]][0][1] * dp[G[current][j]][1][1];
                    ans[current] += dp[G[current][i]][1][1] * dp[G[current][j]][0][1];
                }
            }
        }
        else{
            // mint sum_of_square = 0;
            // vector<vector<mint>> square_of_sum(2, vector<mint>(2, mint(0)));
            // for(auto child : G[current]){
            //     if(child == parent) continue;
            //     for(int w = 0; w < 2; ++w){
            //         for(int l = 0; l < 2; ++l){
            //             sum_of_square += dp[child][w][l] * dp[child][w][l];
            //             square_of_sum[w][l] += dp[child][w][l];
            //         }
            //     }
            // }
            // mint tmp = 0;
            // for(int w = 0; w < 2; ++w){
            //     for(int l = 0; l < 2; ++l){
            //         square_of_sum[w][l] *= square_of_sum[w][l];
            //         tmp += square_of_sum[w][l];
            //     }
            // }
            // ans[current] += (tmp - sum_of_square) / 2;
            for(int i = 0; i < G[current].size(); ++i){
                if(G[current][i] == parent) continue;
                for(int j = i + 1; j < G[current].size(); ++j){
                    if(G[current][j] == parent) continue;
                    ans[current] += dp[G[current][i]][0][0] * dp[G[current][j]][0][0];
                    ans[current] += dp[G[current][i]][1][0] * dp[G[current][j]][1][0];
                    ans[current] += dp[G[current][i]][0][1] * dp[G[current][j]][0][1];
                    ans[current] += dp[G[current][i]][1][1] * dp[G[current][j]][1][1];
                }
            }
        }
        // cerr << "Vertex = " << current << " (End)" << endl;
    };
    
    rec(rec, 1, 0);
    cout << ans[1] << endl;
}