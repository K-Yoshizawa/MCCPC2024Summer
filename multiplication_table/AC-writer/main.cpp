#include <bits/stdc++.h>
using namespace std;

int main(){
    int N; cin >> N;
    string M; cin >> M;

    int m = (M.size() >= 2 ? stoi(M.substr(M.size() - 2)) : stoi(M));
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            printf("%02d%c", (m + i) * (m + j) % 100, j == N - 1 ? '\n' : ' ');
        }
    }
}