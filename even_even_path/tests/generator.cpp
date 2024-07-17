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

enum class TREETYPE{
    RANDOM,
    STAR,
    LINE,
    BINARY,
    HATRED_TYPE1,
    HATRED_TYPE2,
    HATRED_TYPE3,
};

vector<pair<int, int>> make_tree(int N){
    vector<pair<int, int>> ret;
    UnionFind uf(N + 1);
    while(ret.size() < N - 1){
        int A = rnd.next(1, N - 1);
        int B = rnd.next(A + 1, N);
        if(uf.unite(A, B)){
            ret.emplace_back(A, B);
        }
    }
    return ret;
}

vector<pair<int, int>> make_star(int N){
    vector<pair<int, int>> ret;
    vector<int> vertex(N);
    iota(vertex.begin(), vertex.end(), 1);
    shuffle(vertex.begin(), vertex.end());
    for(int i = 1; i < N; ++i){
        ret.emplace_back(min(vertex[i], vertex[0]), max(vertex[i], vertex[0]));
    }
    return ret;
}

vector<pair<int, int>> make_line(int N){
    vector<pair<int, int>> ret;
    vector<int> vertex(N);
    iota(vertex.begin(), vertex.end(), 1);
    shuffle(vertex.begin(), vertex.end());
    for(int i = 0; i < N - 1; ++i){
        ret.emplace_back(min(vertex[i], vertex[i + 1]), max(vertex[i], vertex[i + 1]));
    }
    return ret;
}

vector<pair<int, int>> make_binary(int N){
    vector<pair<int, int>> ret;
    vector<int> vertex(N);
    iota(vertex.begin(), vertex.end(), 1);
    shuffle(vertex.begin(), vertex.end());
    vertex.push_back(0);
    reverse(vertex.begin(), vertex.end());
    for(int i = 1; i <= N; ++i){
        if(i * 2 + 0 <= N) ret.emplace_back(min(vertex[i], vertex[i * 2 + 0]), max(vertex[i], vertex[i * 2 + 0]));
        if(i * 2 + 1 <= N) ret.emplace_back(min(vertex[i], vertex[i * 2 + 1]), max(vertex[i], vertex[i * 2 + 1]));
    }
    return ret;
}

vector<pair<int, int>> make_hatred(int N, int M, int K){
    vector<pair<int, int>> ret;
    vector<int> vertex(N);
    iota(vertex.begin(), vertex.end(), 1);
    shuffle(vertex.begin(), vertex.end());
    // int M = 133, K = 1500;
    for(int i = 0; i < M; ++i){
        int u = vertex[i];
        for(int j = 0; j < K; ++j){
            int v = vertex[M + i * K + j];
            ret.emplace_back(min(u, v), max(u, v));
        }
        if(i > 0) ret.emplace_back(min(u, vertex[i - 1]), max(u, vertex[i - 1]));
    }
    for(int i = M + M * K; i < N; ++i){
        ret.emplace_back(min(vertex[0], vertex[i]), max(vertex[0], vertex[i]));
    }
    return ret;
}

void make_sample_testcase(){
    {
        ofstream of("00_sample_01.in");
        of << "4" << endl;
        of << "0 1 0 1" << endl;
        of << "1 2" << endl;
        of << "2 3" << endl;
        of << "3 4" << endl;
        of.close();
    }
    {
        ofstream of("00_sample_02.in");
        of << "7" << endl;
        of << "0 0 1 1 0 0 1" << endl;
        of << "1 2" << endl;
        of << "2 3" << endl;
        of << "2 4" << endl;
        of << "2 5" << endl;
        of << "2 6" << endl;
        of << "2 7" << endl;
        of.close();
    }
}

void make_easy_testcase(int N, string case_name){
    ofstream of(case_name.c_str());
    of << N << endl;
    for(int i = 1; i <= N; ++i) of << rnd.next(0, 1) << " \n"[i == N];
    for(int i = 1; i <= N - 1; ++i){
        of << i << " " << i + 1 << endl;
    }
    // of << 1 << endl;
    // of << 0 << endl;
    of.close();
}

vector<pair<int, int>> get_tree(int N, TREETYPE tree_type){
    if(tree_type == TREETYPE::STAR) return make_star(N);
    if(tree_type == TREETYPE::LINE) return make_line(N);
    if(tree_type == TREETYPE::BINARY) return make_binary(N);
    if(tree_type == TREETYPE::HATRED_TYPE1) return make_hatred(N, 399, 500);
    if(tree_type == TREETYPE::HATRED_TYPE2) return make_hatred(N, 133, 1500);
    if(tree_type == TREETYPE::HATRED_TYPE3) return make_hatred(N, 99, 2000);
    return make_tree(N);
}

void make_normal_testcase(int N, string case_name, TREETYPE tree_type = TREETYPE::RANDOM){
    ofstream of(case_name.c_str());
    of << N << endl;
    for(int i = 1; i <= N; ++i) of << rnd.next(0, 1) << " \n"[i == N];
    for(auto [A, B] : get_tree(N, tree_type)){
        of << A << " " << B << endl;
    }
    // of << 1 << endl;
    // of << 0 << endl;
    of.close();
}

void make_hard_testcase(int N, int M, string case_name, TREETYPE tree_type = TREETYPE::RANDOM){
    ofstream of(case_name.c_str());
    of << N << endl;
    for(int i = 1; i <= N; ++i) of << rnd.next(0, 1) << " \n"[i == N];
    for(auto [A, B] : get_tree(N, tree_type)){
        of << A << " " << B << endl;
    }
    // of << M << endl;
    // bool prev_zero = false;
    // for(int i = 1; i <= M; ++i){
    //     if(prev_zero){
    //         of << rnd.next(1, N) << " \n"[i == M];
    //         prev_zero = false;
    //     }
    //     else{
    //         if(!rnd.next(2)){
    //             of << 0 << " \n"[i == M];
    //             prev_zero = true;
    //         }
    //         else{
    //             of << rnd.next(1, N) << " \n"[i == M];
    //         }
    //     }
    // }
    of.close();
}

int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);

    // 00 sample
    make_sample_testcase();

    // 1* Easy
    for(int t = 1; t <= 5; ++t){
        make_easy_testcase(rnd.next(1, EASY_MAX_N), format("10_random_%02d.in", t));
    }
    for(int t = 6; t <= 10; ++t){
        make_easy_testcase(EASY_MAX_N, format("10_random_%02d.in", t));
    }
    {
        ofstream of("19_hand_01.in");
        of << "1" << endl;
        of << "0" << endl;
        of.close();
    }
    {
        ofstream of("19_hand_02.in");
        of << "1" << endl;
        of << "1" << endl;
        of.close();
    }

    // 2* Normal
    for(int t = 1; t <= 5; ++t){
        make_normal_testcase(rnd.next(NORMAL_SMALL_MIN_N, NORMAL_SMALL_MAX_N), format("21_small_%02d.in", t));
    }
    for(int t = 1; t <= 5; ++t){
        make_normal_testcase(rnd.next(NORMAL_LARGE_MIN_N, NORMAL_LARGE_MAX_N), format("22_large_%02d.in", t));
    }
    for(int t = 1; t <= 5; ++t){
        make_normal_testcase(NORMAL_MAX_N, format("23_max_%02d.in", t));
    }
    for(int t = 1; t <= 5; ++t){
        make_normal_testcase(NORMAL_MAX_N, format("24_star_%02d.in", t), TREETYPE::STAR);
    }
    for(int t = 1; t <= 5; ++t){
        make_normal_testcase(NORMAL_MAX_N, format("25_line_%02d.in", t), TREETYPE::LINE);
    }
    for(int t = 1; t <= 5; ++t){
        make_normal_testcase(NORMAL_MAX_N, format("26_binary_%02d.in", t), TREETYPE::BINARY);
    }
    for(int t = 1; t <= 3; ++t){
        ofstream of(format("28_zero_%02d.in", t));
        of << NORMAL_MAX_N << endl;
        for(int i = 1; i <= NORMAL_MAX_N; ++i) of << 0 << " \n"[i == NORMAL_MAX_N];
        for(auto [A, B] : get_tree(NORMAL_MAX_N, TREETYPE::RANDOM)){
            of << A << " " << B << endl;
        }
        of.close();
    }
    for(int t = 1; t <= 3; ++t){
        ofstream of(format("29_one_%02d.in", t));
        of << NORMAL_MAX_N << endl;
        for(int i = 1; i <= NORMAL_MAX_N; ++i) of << 1 << " \n"[i == NORMAL_MAX_N];
        for(auto [A, B] : get_tree(NORMAL_MAX_N, TREETYPE::RANDOM)){
            of << A << " " << B << endl;
        }
        of.close();
    }

    // 3* Hard
    for(int t = 1; t <= 5; ++t){
        make_hard_testcase(rnd.next(HARD_SMALL_MIN_N, HARD_SMALL_MAX_N), rnd.next(MIN_M, HARD_MAX_M), format("31_small_%02d.in", t));
    }
    for(int t = 1; t <= 10; ++t){
        make_hard_testcase(rnd.next(HARD_LARGE_MIN_N, HARD_LARGE_MAX_N), rnd.next(MIN_M, HARD_MAX_M), format("32_large_%02d.in", t));
    }
    for(int t = 1; t <= 5; ++t){
        make_hard_testcase(MAX_N, HARD_MAX_M, format("33_max_%02d.in", t));
    }
    for(int t = 1; t <= 5; ++t){
        make_hard_testcase(MAX_N, HARD_MAX_M, format("34_star_%02d.in", t), TREETYPE::STAR);
    }
    for(int t = 1; t <= 5; ++t){
        make_hard_testcase(MAX_N, HARD_MAX_M, format("35_line_%02d.in", t), TREETYPE::LINE);
    }
    for(int t = 1; t <= 5; ++t){
        make_hard_testcase(MAX_N, HARD_MAX_M, format("36_binary_%02d.in", t), TREETYPE::BINARY);
    }
    for(int t = 1; t <= 5; ++t){
        make_hard_testcase(MAX_N, HARD_MAX_M, format("37_hatred_%02d.in", t), TREETYPE::HATRED_TYPE1);
    }
    for(int t = 6; t <= 10; ++t){
        make_hard_testcase(MAX_N, HARD_MAX_M, format("37_hatred_%02d.in", t), TREETYPE::HATRED_TYPE2);
    }
    for(int t = 11; t <= 15; ++t){
        make_hard_testcase(MAX_N, HARD_MAX_M, format("37_hatred_%02d.in", t), TREETYPE::HATRED_TYPE3);
    }
    for(int t = 1; t <= 3; ++t){
        ofstream of(format("38_zero_%02d.in", t));
        of << MAX_N << endl;
        for(int i = 1; i <= MAX_N; ++i) of << 0 << " \n"[i == MAX_N];
        for(auto [A, B] : get_tree(MAX_N, TREETYPE::RANDOM)){
            of << A << " " << B << endl;
        }
        of.close();
    }
    for(int t = 1; t <= 3; ++t){
        ofstream of(format("39_one_%02d.in", t));
        of << MAX_N << endl;
        for(int i = 1; i <= MAX_N; ++i) of << 1 << " \n"[i == MAX_N];
        for(auto [A, B] : get_tree(MAX_N, TREETYPE::RANDOM)){
            of << A << " " << B << endl;
        }
        of.close();
    }

    return 0;
}