#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main(){
    int N; cin >> N;
    assert(N <= 1000);
    vector<int> A(N);
    for(auto &a : A) cin >> a;

    vector left_cum(N + 1, vector<int>(N, 0));
    vector right_cum(N + 1, vector<int>(N, 0));
    for(int i = 0; i < N; ++i){
        ++left_cum[A[i]][i];
        ++right_cum[A[i]][i];
    }
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j < N; ++j){
            left_cum[i][j] += left_cum[i][j - 1];
        }
        for(int j = N - 2; j >= 0; --j){
            right_cum[i][j] += right_cum[i][j + 1];
        }
    }

    int ans = 0;
    for(int i = 0; i < N; ++i){
        for(int j = 1; j <= N; ++j){
            if(j == A[i]) continue;
            ans += left_cum[j][i] * (right_cum[A[i]][i] - 1);
        }
    }

    cout << ans << endl;
}