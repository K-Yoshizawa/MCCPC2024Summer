#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main(){
    int N; cin >> N;
    assert(N <= 100);
    vector<int> A(N);
    for(auto &a : A) cin >> a;

    int ans = 0;
    for(int i = 0; i < N; ++i){
        for(int j = i + 1; j < N; ++j){
            for(int k = j + 1; k < N; ++k){
                if(A[i] != A[j] and A[j] == A[k]) ++ans;
            }
        }
    }
    cout << ans << endl;
}