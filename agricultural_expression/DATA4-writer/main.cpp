#include <bits/stdc++.h>
using namespace std;

string S;

pair<string, int> grow(int start){
    string ret;
    int idx = start, cnt = 0;
    while(isdigit(S[idx])){
        ret.push_back(min('9', char(S[idx] + 1)));
        ++idx, ++cnt;
    }
    return {ret, cnt};
}

pair<string, int> heavest(int start){
    int ret = 0;
    int idx = start, cnt = 0;
    while(isdigit(S[idx])){
        ret += (S[idx] - '0');
        ++idx, ++cnt;
    }
    return {to_string(ret), cnt};
}

int main(){
    cin >> S;

    int idx = 2;
    if(S[0] == 'G'){
        auto [ret, cnt] = grow(2);
        cout << ret;
        idx += cnt + 2;
    }
    else{
        auto [ret, cnt] = heavest(2);
        cout << ret;
        idx += cnt + 2;
    }
    
    if(S[idx] == 'G'){
        auto [ret, cnt] = grow(idx + 2);
        cout << ret;
    }
    else{
        auto [ret, cnt] = heavest(idx + 2);
        cout << ret;
    }
    cout << endl;
}