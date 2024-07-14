#include <bits/stdc++.h>
using namespace std;

int main(){
    string S; cin >> S;

    for(auto c : S){
        if(c != '+') cout << c;
    }
    cout << endl;
}