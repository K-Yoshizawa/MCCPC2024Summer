#include <bits/stdc++.h>

using namespace std;

// <expr> := <term> | <term> + '+' + <expr>
// <term> := <grow> | <heavest> | <number>
// <grow> := 'G(' + <expr> + ')'
// <harvest> := 'H(' + <expr> + ')'
// <number> := <digit> | <digit> <number>
// <digit> := '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'

class Parser
{
    string S;
    int pos = 0;

public:
    Parser(string S) : S(S) {}

    char peek()
    {
        return pos < S.size() ? S[pos] : 'a';
    }

    void next(string S)
    {
        for (const auto &s : S)
        {
            assert(peek() == s);
            pos++;
        }
    }

    string expr()
    {
        string res = term();
        if (peek() == '+')
        {
            next("+");
            res += expr();
        }
        return res;
    }

    string term()
    {
        if (peek() == 'G')
            return grow();
        if (peek() == 'H')
            return harvest();
        return number();
    }

    string g(string S)
    {
        string res = "";
        for (auto s : S)
        {
            assert('0' <= s and s <= '9');
            if (s == '9')
                res += s;
            else
            {
                s += 1;
                res += s;
            }
        }
        return res;
    }

    string grow()
    {
        next("G(");
        string res = expr();
        next(")");
        return g(res);
    }

    string h(string S){
        int res = 0;
        for (auto s : S){
            assert('0' <= s and s <= '9');
            res += s - '0';
        }
        return to_string(res);
    }

    string harvest()
    {
        next("H(");
        string res = expr();
        next(")");
        return h(res);
    }

    string number(){
        string res = "";
        while ('0' <= peek() and peek() <= '9'){
            res += peek();
            pos++;
        }
        return res;
    }
};

int main(int argc, char *argv[]){
    string s; cin >> s;

    Parser p(s);
    cout << p.expr() << endl;
}