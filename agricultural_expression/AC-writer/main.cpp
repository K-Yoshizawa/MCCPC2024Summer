#include <bits/stdc++.h>
using namespace std;

struct Parser{
    string s;
    string::const_iterator itr;

    Parser(string _s) : s(_s){
        itr = s.begin();
    }

    struct Data{
        string t;
        int add;
        array<int, 10> dig;

        Data(string str = "") : t(str){
            add = 0;
            dig.fill(0);
            for(auto c : t) ++dig[c - '0'];
        }
    };

    string parse(){
        return expr().t;
    }

    Data expr(){
        Data ret = term();

        string x = ret.t;
        for(auto &c : x){
            c = min('9', (char)(c + ret.add));
        }
        while(itr != s.end() and *itr == '+'){
            ++itr;
            auto rig = term();
            for(auto &c : rig.t){
                c = min('9', (char)(c + rig.add));
            }
            x.append(rig.t);
        }
        return Data(x);
    }

    Data term(){
        Data ret;

        if(*itr == 'G'){
            ret = grow();
        }
        else if(*itr == 'H'){
            ret = harvest();
        }
        else{
            ret = number();
        }
        
        return ret;
    }

    Data grow(){
        assert(*itr == 'G');
        ++itr;
        ++itr;
        auto ret = expr();
        ++ret.add;
        ++itr;
        return ret;
    }

    Data harvest(){
        assert(*itr == 'H');
        ++itr;
        ++itr;
        auto x = expr();
        int sum = 0;
        for(int i = 0; i < 10; ++i) sum += x.dig[i] * min(9, x.add + i);
        Data ret(to_string(sum));
        ++itr;
        return ret;
    }

    Data number(){
        string str;
        while(isdigit(*itr)){
            str.push_back(*itr);
            ++itr;
        }
        return Data(str);
    }
};

int main(){
    string S; cin >> S;
    cout << Parser(S).parse() << endl;
}