#include <bits/stdc++.h>
#include "testlib.h"
#include "constrains.h"
using namespace std;

struct Parser{
    string s;
    string::const_iterator itr;

    Parser(string _s) : s(_s){
        itr = s.begin();
    }

    bool parse(){
        return expr();
    }

    bool expr(){
        bool ret = term();

        while(itr != s.end() and *itr == '+'){
            ret &= (*itr == '+');
            ++itr;
            ret &= expr();
        }
        return ret;
    }

    bool term(){
        bool ret = true;

        if(*itr == 'G'){
            ret &= grow();
        }
        else if(*itr == 'H'){
            ret &= harvest();
        }
        else{
            ret &= number();
        }
        
        return ret;
    }

    bool grow(){
        bool ret = true;
        ret &= (*itr == 'G');
        ++itr;
        ret &= (*itr == '(');
        ++itr;
        ret &= expr();
        ret &= (*itr == ')');
        ++itr;
        return ret;
    }

    bool harvest(){
        bool ret = true;
        ret &= (*itr == 'H');
        ++itr;
        ret &= (*itr == '(');
        ++itr;
        ret &= expr();
        ret &= (*itr == ')');
        ++itr;
        return ret;
    }

    bool number(){
        bool ret = false;
        while(isdigit(*itr)){
            ret = true;
            ++itr;
        }
        return ret;
    }
};

int main(int argc, char* argv[]){
    registerValidation(argc, argv);
    string S = inf.readToken("[GH()+0-9]{1, 500000}", "S");
    inf.readEoln();
    inf.readEof();
    assert(Parser(S).parse());
    return 0;
}