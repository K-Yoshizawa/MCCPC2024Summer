#include <bits/stdc++.h>
using namespace std;

string S;

string simple(int start, int end){
    string ret;
    if(S[start] == 'G'){
        ret = S.substr(start + 2, end - start - 3);
        for(auto &c : ret) c = min('9', char(c + 1));
    }
    else if(S[start] == 'H'){
        ret = S.substr(start + 2, end - start - 3);
        int ans = 0;
        for(auto c : ret) ans += (c - '0');
        ret = to_string(ans);
    }
    else{
        for(int i = start; i < end; ++i){
            if(S[i] != '+') ret.push_back(S[i]);
        }
    }
    return ret;
}

string nested_grow(int start, int end){
    string ret = simple(start, end);
    for(auto &c : ret) c = min('9', char(c + 1));
    return ret;
}

string nested_heavest(int start, int end){
    string ret = simple(start, end);
    int sum = 0;
    for(auto &c : ret) sum += (c - '0');
    return to_string(sum);
}

int main(){
    cin >> S;

    int idx = 0;
    if(S[idx] == 'G'){
        int start = idx + 2, end = start + 1, nest = 1;
        while(1){
            if(S[end] == '(') ++nest;
            if(S[end] == ')') --nest;
            if(nest == 0) break;
            ++end;
        }
        idx = end + 2;
        cout << nested_grow(start, end);
    }
    else if(S[idx] == 'H'){
        int start = idx + 2, end = start + 1, nest = 1;
        while(1){
            if(S[end] == '(') ++nest;
            if(S[end] == ')') --nest;
            if(nest == 0) break;
            ++end;
        }
        idx = end + 2;
        cout << nested_heavest(start, end);
    }
    else{
        cout << simple(0, S.size()) << endl;
        return 0;
    }

    while(idx < S.size()){
        if(S[idx] == 'G'){
            int start = idx + 2, end = start + 1, nest = 1;
            while(1){
                if(S[end] == '(') ++nest;
                if(S[end] == ')') --nest;
                if(nest == 0) break;
                ++end;
            }
            idx = end + 2;
            cout << nested_grow(start, end);
        }
        else{
            int start = idx + 2, end = start + 1, nest = 1;
            while(1){
                if(S[end] == '(') ++nest;
                if(S[end] == ')') --nest;
                if(nest == 0) break;
                ++end;
            }
            idx = end + 2;
            cout << nested_heavest(start, end);
        }
    }
    cout << endl;
}