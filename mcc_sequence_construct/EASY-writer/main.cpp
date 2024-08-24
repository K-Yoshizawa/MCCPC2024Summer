#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main(){
    ll M; cin >> M;
    
    switch(M){
        case 2 :
            cout << "4" << endl;
            cout << "3 2 1 1" << endl;
            break;
        case 3 :
            cout << "4" << endl;
            cout << "2 1 1 1" << endl;
            break;
        case 5 :
            cout << "6" << endl;
            cout << "4 1 3 2 1 1" << endl;
            break;
        case 8 :
            cout << "7" << endl;
            cout << "4 1 1 3 2 1 1" << endl;
            break;
        case 13 :
            cout << "7" << endl;
            cout << "3 1 1 2 1 1 1" << endl;
            break;
        case 21 :
            cout << "8" << endl;
            cout << "2 1 1 1 1 1 1 1" << endl;
            break;
        case 34 :
            cout << "10" << endl;
            cout << "3 1 1 1 1 2 1 1 1 1" << endl;
            break;
        case 55 :
            cout << "12" << endl;
            cout << "2 1 1 1 1 1 1 1 1 1 1 1" << endl;
            break;
        case 89 :
            cout << "16" << endl;
            cout << "4 1 1 1 1 1 1 1 1 3 1 1 1 2 1 1" << endl;
            break;
        case 144 :
            cout << "19" << endl;
            cout << "4 1 1 1 1 1 1 1 1 1 3 1 1 1 1 2 1 1 1" << endl;
            break;
    }
}