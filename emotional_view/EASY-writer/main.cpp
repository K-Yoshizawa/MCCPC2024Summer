#include <bits/stdc++.h>
using namespace std;

int main(){
    int N; cin >> N;
    vector<int> x(N), y(N), r(N);
    for(int i = 0; i < N; ++i) cin >> x[i] >> y[i] >> r[i];

    int leftest_above = 3000, leftest_middle = 3000, leftest_below = 3000;
    int ans_above = 0, ans_middle = 0, ans_below = 0;
    for(int i = 0; i < N; ++i){
        if(y[i] == 0){
            if(x[i] < leftest_middle){
                leftest_middle = x[i];
                ans_middle = i + 1;
            }
        }
        else if(y[i] == x[i]){
            if(x[i] < leftest_above){
                leftest_above = x[i];
                ans_above = i + 1;
            }
        }
        else{
            if(x[i] < leftest_below){
                leftest_below = x[i];
                ans_below = i + 1;
            }
        }
    }
    array<int, 3> ans{ans_above, ans_middle, ans_below};
    sort(ans.begin(), ans.end());
    for(int i = 0; i < 3; ++i){
        if(ans[i] == 0) continue;
        cout << ans[i] << " \n"[i == 2];
    }
}