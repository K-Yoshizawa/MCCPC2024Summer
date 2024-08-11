#include <bits/stdc++.h>
#include "testlib.h"
#include "constrains.h"
using namespace std;

struct UnionFind {
    vector< int > data;
    
    UnionFind(int sz) {
        data.assign(sz, -1);
    }
    
    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if(x == y) return (false);
        if(data[x] > data[y]) swap(x, y);
        data[x] += data[y];
        data[y] = x;
        return (true);
    }
    
    int find(int k) {
        if(data[k] < 0) return (k);
        return (data[k] = find(data[k]));
    }
};

ll CalcMaxDist(int N, int M, vector<tuple<int, int, int>> &G_origin){
    vector<vector<pair<int, int>>> G(N + 1);
    for(int i = 0; i < M; ++i){
        auto [A, B, C] = G_origin[i];
        G[A].emplace_back(B, C);
        G[B].emplace_back(A, C);
    }
    using p = pair<ll, ll>;
    ll INF = (ll)1e15;
    priority_queue<p, vector<p>, greater<p>> que;
    vector<ll> alice(N + 1, INF), bob(N + 1, INF);
    alice[1] = bob[N] = 0;
    que.emplace(0, 1);
    while(que.size()){
        auto [d, v] = que.top(); que.pop();
        if(alice[v] != d) continue;
        for(auto [u, c] : G[v]){
            ll nd = d + c;
            if(nd < alice[u]){
                alice[u] = nd;
                que.emplace(nd, u);
            }
        }
    }
    que.emplace(0, N);
    while(que.size()){
        auto [d, v] = que.top(); que.pop();
        if(bob[v] != d) continue;
        for(auto [u, c] : G[v]){
            ll nd = d + c;
            if(nd < bob[u]){
                bob[u] = nd;
                que.emplace(nd, u);
            }
        }
    }
    ll ret = 0;
    for(int i = 1; i <= N; ++i) ret = max({ret, alice[i], bob[i]});
    return ret;
}

vector<ll> DijkstraWithSort(int N, int M, vector<tuple<int, int, int>> &G_origin){
    vector<vector<pair<int, int>>> G(N + 1);
    for(int i = 0; i < M; ++i){
        auto [A, B, C] = G_origin[i];
        G[A].emplace_back(B, C);
        G[B].emplace_back(A, C);
    }
    using p = pair<ll, ll>;
    ll INF = (ll)1e15;
    priority_queue<p, vector<p>, greater<p>> que;
    vector<ll> alice(N + 1, INF), bob(N + 1, INF);
    alice[1] = bob[N] = 0;
    que.emplace(0, 1);
    while(que.size()){
        auto [d, v] = que.top(); que.pop();
        if(alice[v] != d) continue;
        for(auto [u, c] : G[v]){
            ll nd = d + c;
            if(nd < alice[u]){
                alice[u] = nd;
                que.emplace(nd, u);
            }
        }
    }
    que.emplace(0, N);
    while(que.size()){
        auto [d, v] = que.top(); que.pop();
        if(bob[v] != d) continue;
        for(auto [u, c] : G[v]){
            ll nd = d + c;
            if(nd < bob[u]){
                bob[u] = nd;
                que.emplace(nd, u);
            }
        }
    }
    vector<ll> ret(N + 1, 0);
    for(int i = 1; i <= N; ++i) ret[i] = max(alice[i], bob[i]);
    sort(ret.begin() + 1, ret.end());
    return ret;
}

set<pair<int, int>> make_tree(int N){
    set<pair<int, int>> ret;
    UnionFind uf(N + 1);
    while(ret.size() < N - 1){
        int A = rnd.next(1, N - 1);
        int B = rnd.next(A + 1, N);
        if(uf.unite(A, B)){
            ret.emplace(A, B);
        }
    }
    return ret;
}

void make_sample_testcase(){
    {
        ofstream of("00_sample_01.in");
        of << "6 5" << endl;
        of << "1 2 2" << endl;
        of << "2 3 7" << endl;
        of << "2 4 1" << endl;
        of << "2 5 8" << endl;
        of << "2 6 2" << endl;
        of << "3" << endl;
        of << "4 10 1" << endl;
        of.close();
    }
    {
        ofstream of("00_sample_02.in");
        of << "8 7" << endl;
        of << "1 3 5" << endl;
        of << "2 3 4" << endl;
        of << "3 4 4" << endl;
        of << "4 7 8" << endl;
        of << "5 6 3" << endl;
        of << "6 8 7" << endl;
        of << "7 8 7" << endl;
        of << "3" << endl;
        of << "15 20 25" << endl;
        of.close();
    }
    {
        ofstream of("00_sample_03.in");
        of << "8 12" << endl;
        of << "1 3 5" << endl;
        of << "1 5 8" << endl;
        of << "2 3 4" << endl;
        of << "2 4 3" << endl;
        of << "3 4 4" << endl;
        of << "3 6 5" << endl;
        of << "4 6 4" << endl;
        of << "4 7 8" << endl;
        of << "5 6 3" << endl;
        of << "5 7 9" << endl;
        of << "6 8 7" << endl;
        of << "7 8 7" << endl;
        of << "5" << endl;
        of << "8 11 13 15 16" << endl;
        of.close();
    }
}

void make_easy_testcase(int N, int T, string case_name, int type = 0){
    vector<tuple<int, int, int>> G;
    int M = N - 1;
    for(int i = 1; i <= N; ++i){
        if(i == 2) continue;
        int C;
        if(type == 0) C = rnd.next(MIN_C, 100000);
        if(type == 1) C = MAX_C;
        G.emplace_back(min(2, i), max(2, i), C);
    }
    ofstream of(case_name.c_str());
    of << N << " " << M << endl;
    for(auto [A, B, C] : G){
        of << A << " " << B << " " << C << endl;
    }
    of << T << endl;
    if(type == 0){
        auto max_K = CalcMaxDist(N, M, G);
        max_K = min(max_K, (ll)MAX_K);
        for(int t = 1; t <= T; ++t){
            of << rnd.next(0LL, max_K) << (t == T ? '\n' : ' ');
        }
    }
    if(type == 1){
        auto Ks = DijkstraWithSort(N, M, G);
        for(int t = 1; t <= T; ++t){
            of << min((ll)MAX_K, Ks[t]) << (t == T ? '\n' : ' ');
        }
    }
    of.close();
}

void make_normal_testcase(int N, ll M, string case_name){
}

void make_hard_testcase(int N, int M, int T, string case_name, int type = 0){
    auto es = make_tree(N);
    while(es.size() < M){
        int A = rnd.next(1, N - 1);
        int B = rnd.next(A + 1, N);
        if(es.count({A, B})) continue;
        es.emplace(A, B);
    }
    vector<tuple<int, int, int>> G;
    for(auto [A, B] : es){
        int C;
        if(type == 0) C = rnd.next(MIN_C, MAX_C);
        if(type == 1) C = rnd.next(MIN_C, 1000);
        if(type == 2) C = rnd.next(MIN_C, 10);
        G.emplace_back(A, B, C);
    }
    ofstream of(case_name.c_str());
    of << N << " " << M << endl;
    for(auto [A, B, C] : G){
        of << A << " " << B << " " << C << endl;
    }
    of << T << endl;
    if(type == 0 or type == 2){
        auto max_K = CalcMaxDist(N, M, G);
        max_K = min(max_K, (ll)MAX_K);
        for(int t = 1; t <= T; ++t){
            of << rnd.next(0LL, max_K) << (t == T ? '\n' : ' ');
        }
    }
    if(type == 1){
        auto Ks = DijkstraWithSort(N, M, G);
        for(int t = 1; t <= T; ++t){
            of << min((ll)MAX_K, Ks[t]) << (t == T ? '\n' : ' ');
        }
    }
    of.close();
}

int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);

    // 00 sample
    make_sample_testcase();

    // 1* Easy
    for(int t = 1; t <= 7; ++t){
        int N = rnd.next(LARGE_MIN_N, LARGE_MAX_N);
        int T = NORMAL_MAX_T;
        make_easy_testcase(N, T, format("10_random_%02d.in", t));
    }
    for(int t = 1; t <= 3; ++t){
        int N = MAX_N;
        int T = NORMAL_MAX_T;
        make_easy_testcase(N, T, format("11_max_%02d.in", t));
    }
    // for(int t = 1; t <= 3; ++t){
    //     int N = MAX_N;
    //     int T = NORMAL_MAX_T;
    //     make_easy_testcase(N, T, format("12_use_64_bit_%02d.in", t), 1);
    // }
    
    // 2* Normal
    for(int t = 1; t <= 10; ++t){
        int N = rnd.next(LARGE_MIN_N, LARGE_MAX_N);
        int LIM_M = min((ll)N * (N - 1) / 2, (ll)MAX_M);
        int M = N - 1;
        int T = NORMAL_MAX_T;
        make_hard_testcase(N, M, T, format("20_random_%02d.in", t));
    }
    for(int t = 1; t <= 5; ++t){
        int N = MAX_N;
        int LIM_M = min((ll)N * (N - 1) / 2, (ll)MAX_M);
        int M = N - 1;
        int T = NORMAL_MAX_T;
        make_hard_testcase(N, M, T, format("21_max_%02d.in", t));
    }
    for(int t = 1; t <= 5; ++t){
        int N = rnd.next(LARGE_MIN_N, LARGE_MAX_N);
        int LIM_M = min((ll)N * (N - 1) / 2, (ll)MAX_M);
        int M = N - 1;
        int T = NORMAL_MAX_T;
        make_hard_testcase(N, M, T, format("23_sort_%02d.in", t), 1);
    }

    // 3* Hard
    for(int t = 1; t <= 10; ++t){
        int N = rnd.next(LARGE_MIN_N, LARGE_MAX_N);
        int LIM_M = min((ll)N * (N - 1) / 2, (ll)MAX_M);
        int M = rnd.next(N - 1, LIM_M);
        int T = MAX_T;
        make_hard_testcase(N, M, T, format("30_random_%02d.in", t));
    }
    for(int t = 1; t <= 5; ++t){
        int N = MAX_N;
        int LIM_M = min((ll)N * (N - 1) / 2, (ll)MAX_M);
        int M = MAX_M;
        int T = MAX_T;
        make_hard_testcase(N, M, T, format("31_max_%02d.in", t));
    }
    for(int t = 1; t <= 5; ++t){
        int N = rnd.next(LARGE_MIN_N, LARGE_MAX_N);
        int LIM_M = min((ll)N * (N - 1) / 2, (ll)MAX_M);
        int M = N - 1;
        int T = MAX_T;
        make_hard_testcase(N, M, T, format("32_tree_%02d.in", t));
    }
    for(int t = 1; t <= 5; ++t){
        int N = rnd.next(LARGE_MIN_N, LARGE_MAX_N);
        int LIM_M = min((ll)N * (N - 1) / 2, (ll)MAX_M);
        int M = rnd.next(N - 1, LIM_M);
        int T = N;
        make_hard_testcase(N, M, T, format("33_sort_%02d.in", t), 1);
    }

    {
        ofstream of("29_killer_01_may_use_maxheap.in");
        int chain = 0;
        while((1LL << chain) + MIN_C * 2 <= MAX_C) ++chain;
        int way = (MAX_N - 2) / (chain * 2);
        int N = way * (chain * 2) + 2;
        int s = 0, t = N - 1;
        vector<tuple<int, int, int>> G;
        auto add = [&](int v, int u, int C){
            int A = min(v, u) + 1, B = max(v, u) + 1;
            G.emplace_back(A, B, C);
        };
        int v = 1, A, B;
        for(int i = 0; i < way; ++i){
            int pv = s;
            for(int j = chain - 1; j >= 0; --j){
                add(pv, v + j, (1LL << j) + MIN_C * 2);
                add(pv, v + chain + j, MIN_C);
                add(v + chain + j, v + j, MIN_C);
                pv = v + j;
            }
            add(v, t, MAX_C);
            v += chain * 2;
        }
        int M = (int)G.size();
        of << N << " " << M << endl;
        for(auto [A, B, C] : G){
            of << A << " " << B << " " << C << endl;
        }
        int T = 100;
        of << T << endl;
        for(int t = 1; t <= T; ++t){
            int K = rnd.next(MIN_K, MAX_K);
            of << K << (t == T ? '\n' : ' ');
        }
        of.close();
    }
    {
        ofstream of("29_killer_02_may_forget_continue.in");
        int N = MAX_N / 2;
        N = min(N, MAX_M / 2 + 2);
        int s = 0, t = N - 1;
        vector<tuple<int, int, int>> G;
        auto add = [&](int v, int u, int C){
            int A = min(v, u) + 1, B = max(v, u) + 1;
            G.emplace_back(A, B, C);
        };
        for(int i = 0; i < N - 3; ++i){
            add(s, i + 1, MIN_C + i);
            add(i + 1, t - 1, MAX_C - i * 2);
        }
        add(t - 1, t, MAX_C);
        int M = (int)G.size();
        of << N << " " << M << endl;
        for(auto [A, B, C] : G){
            of << A << " " << B << " " << C << endl;
        }
        int T = 100;
        of << T << endl;
        for(int t = 1; t <= T; ++t){
            int K = rnd.next(MIN_K, MAX_K);
            of << K << (t == T ? '\n' : ' ');
        }
        of.close();
    }

    // for(int t = 1; t <= 1; ++t){
    //     make_hard_testcase(8, 7, 5, format("90_random_%02d.in", t), 2);
    // }
    // for(int t = 1; t <= 1; ++t){
    //     make_hard_testcase(8, 12, 5, format("91_random_%02d.in", t), 2);
    // }

    return 0;
}