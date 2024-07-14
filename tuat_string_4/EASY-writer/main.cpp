#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main(){
    int N; cin >> N;
    string S; cin >> S;

    ll ans = 0;
    for(int i = 0; i < N; ++i){
        for(int j = i + 1; j < N; ++j){
            for(int k = j + 1; k < N; ++k){
                for(int l = k + 1; l < N; ++l){
                    if(S[i] == S[l] and S[i] != S[j] and S[i] != S[k] and S[j] != S[k]){
                        ++ans;
                    }
                }
            }
        }
    }
    cout << ans << endl;
}