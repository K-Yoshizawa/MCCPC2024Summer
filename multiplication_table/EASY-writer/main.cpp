#include <bits/stdc++.h>
using namespace std;

int main(){
    int N; cin >> N;
    int M; cin >> M;

    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            printf("%d%c", (M + i) * (M + j) % 100, j == N - 1 ? '\n' : ' ');
        }
    }
}