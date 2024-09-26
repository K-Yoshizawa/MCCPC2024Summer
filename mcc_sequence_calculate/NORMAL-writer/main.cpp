// C++ Solution (Normal)

#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

using ll = long long;

int main(){
    int N; cin >> N;
    assert(N <= 1000);
    vector<int> A(N);
    for(auto &a : A) cin >> a;

    int ans = 0;
    vector C(N + 1, vector(N + 1, 0));
    for(int k = 0; k < N; ++k){
        int Aj = A[k];
        for(int Ai = 1; Ai <= N; ++Ai){
            if(Ai == Aj) continue;
            ans += C[Ai][Aj];
        }
        for(int j = k, i = 0; i < j; ++i){
            ++C[A[i]][Aj];
        }
    }

    cout << ans << endl;
}