#include <bits/stdc++.h>
using namespace std;

int main(){
    string S; cin >> S;

    string T = S.substr(2, S.size() - 3);
    if(S[0] == 'G'){
        for(auto &c : T) c = min('9', char(c + 1));
        cout << T << endl;
    }
    else if(S[0] == 'H'){
        int ans = 0;
        for(auto c : T) ans += (c - '0');
        cout << ans << endl;
    }
    else{
        for(auto c : S){
            if(c != '+') cout << c;
        }
        cout << endl;
    }
}