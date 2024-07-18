#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main(){
    ll M; cin >> M;
    
    switch(M){
        case 0 :
            cout << "3" << endl;
            cout << "1 1 1" << endl;
            break;
        case 1 :
            cout << "3" << endl;
            cout << "2 1 1" << endl;
            break;
        case 2 :
            cout << "4" << endl;
            cout << "3 2 1 1" << endl;
            break;
        case 3 :
            cout << "4" << endl;
            cout << "2 1 1 1" << endl;
            break;
        case 4 :
            cout << "5" << endl;
            cout << "3 1 2 1 1" << endl;
            break;
        case 5 :
            cout << "6" << endl;
            cout << "4 1 3 2 1 1" << endl;
            break;
    }
}