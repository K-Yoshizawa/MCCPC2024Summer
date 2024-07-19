#include <bits/stdc++.h>
#include "testlib.h"
#include "constrains.h"
using namespace std;

void make_sample_testcase(){
    {
        ofstream of("00_sample_01.in");
        of << "5" << endl;
        of << "1 2" << endl;
        of << "2 3" << endl;
        of << "3 4" << endl;
        of << "4 5" << endl;
        of << "2 5" << endl;
        of << "1" << endl;
        of << "5 2" << endl;
        of.close();
    }
    {
        ofstream of("00_sample_02.in");
        of << "5" << endl;
        of << "1 2" << endl;
        of << "2 3" << endl;
        of << "3 4" << endl;
        of << "4 5" << endl;
        of << "2 5" << endl;
        of << "1" << endl;
        of << "5 3" << endl;
        of.close();
    }
    {
        ofstream of("00_sample_03.in");
        of << "9" << endl;
        of << "1 2" << endl;
        of << "2 3" << endl;
        of << "3 4" << endl;
        of << "4 5" << endl;
        of << "5 6" << endl;
        of << "1 6" << endl;
        of << "4 7" << endl;
        of << "7 8" << endl;
        of << "6 9" << endl;
        of << "1" << endl;
        of << "8 9" << endl;
        of.close();
    }
}

void make_easy_testcase(int N, string case_name, int is_circle = -1, int B_on_circle = -1){
    int A = N, B, C;
    if(is_circle == -1) C = rnd.next(1, N - 2);
    else C = is_circle ? 1 : rnd.next(2, N - 2);
    if(B_on_circle == -1) B = rnd.next(1, N - 1);
    else B = B_on_circle ? rnd.next(C, N - 1) : rnd.next(1, C - 1);
    vector<pair<int, int>> G;
    for(int i = 1; i < N; ++i) G.push_back({i, i + 1});
    G.push_back({C, N});

    ofstream of(case_name.c_str());
    of << N << endl;
    for(auto [u, v] : G){
        of << u << " " << v << endl;
    }
    of << 1 << endl;
    of << A << " " << B << endl;
    of.close();
}

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

pair<vector<pair<int, int>>, vector<vector<int>>> make_pseudotree(int N, bool is_cycle = false){
    vector<int> vertex(N);
    iota(vertex.begin(), vertex.end(), 1);
    shuffle(vertex.begin(), vertex.end());
    int branch_amount = is_cycle ? 0 : rnd.next(1, N - 3);
    vector<vector<int>> ret_second(branch_amount + 1);
    for(int i = 0; i < 3; ++i){
        ret_second[0].push_back(vertex[i]);
    }
    for(int i = 1, j = 3; i <= branch_amount; ++i, ++j){
        ret_second[i].push_back(vertex[j]);
    }
    // cerr << "CHECK_A : " << branch_amount << endl;
    int ratio = rnd.next(25, 75);
    for(int i = 3 + branch_amount; i < N; ++i){
        if(rnd.next(1, 100) <= ratio or branch_amount == 0){
            ret_second[0].push_back(vertex[i]);
        }
        else{
            ret_second[rnd.next(1, branch_amount)].push_back(vertex[i]);
        }
    }
    // cerr << "CHECK_B" << endl;
    for(int i = 1; i <= branch_amount; ++i){
        ret_second[i].push_back(rnd.any(ret_second[0]));
    }
    vector<pair<int, int>> ret_first;
    for(int i = 0; i < ret_second[0].size(); ++i){
        int a = ret_second[0][i], b = ret_second[0][(i + 1) % ret_second[0].size()];
        ret_first.emplace_back(min(a, b), max(a, b));
    }
    for(int i = 1; i < ret_second.size(); ++i){
        for(int j = 0; j < ret_second[i].size() - 1; ++j){
            int a = ret_second[i][j], b = ret_second[i][j + 1];
            ret_first.emplace_back(min(a, b), max(a, b));
        }
    }
    return {ret_first, ret_second};
}

enum class QUERY{
    BRANCH_SAME,
    BRANCH_ROOT,
    ROOT_BRANCH,
    BRANCH_COMMON,
    CYCLE_CYCLE,
    CYCLE_BRANCH,
    BRANCH_CYCLE,
    BRANCH_DIFF,
    DUMMY,
};

pair<int, int> make_query(vector<vector<int>> &H, QUERY query_type){
    int A = -1, B = -1;
    int a, b, c;
    int branch_amount = H.size() - 1, branch_size;
    map<int, vector<int>> branch_root;
    for(int i = 1; i <= branch_amount; ++i) branch_root[H[i].back()].push_back(i);
    vector<bool> able_flag(static_cast<int>(QUERY::DUMMY), true);
    {
        int cnt = 0;
        for(int i = 1; i <= branch_amount; ++i) cnt = max(cnt, (int)H[i].size());
        able_flag[static_cast<int>(QUERY::BRANCH_SAME)] = cnt > 2;
    }
    {
        able_flag[static_cast<int>(QUERY::BRANCH_ROOT)] =
        able_flag[static_cast<int>(QUERY::ROOT_BRANCH)] =
        able_flag[static_cast<int>(QUERY::CYCLE_BRANCH)] =
        able_flag[static_cast<int>(QUERY::BRANCH_CYCLE)] = branch_amount >= 1;
    }
    {
        able_flag[static_cast<int>(QUERY::BRANCH_DIFF)] = branch_amount >= 2 && branch_root.size() >= 2;
        bool common_flag = false;
        for(auto [key, value] : branch_root) common_flag |= value.size() >= 2;
        able_flag[static_cast<int>(QUERY::BRANCH_COMMON)] = branch_amount >= 2 && common_flag;
    }
    if(!able_flag[static_cast<int>(query_type)]) return {-1, -1};
    switch(query_type){
        case QUERY::BRANCH_SAME :
            c = rnd.next(1, branch_amount);
            while(H[c].size() <= 2) c = rnd.next(1, branch_amount);
            branch_size = H[c].size() - 1;
            A = B = H[c][rnd.next(branch_size)];
            while(A == B) B = H[c][rnd.next(branch_size)];
            break;
        case QUERY::BRANCH_ROOT :
            c = rnd.next(1, branch_amount);
            branch_size = H[c].size() - 1;
            A = H[c][rnd.next(branch_size)], B = H[c][branch_size];
            break;
        case QUERY::ROOT_BRANCH :
            c = rnd.next(1, branch_amount);
            branch_size = H[c].size() - 1;
            B = H[c][rnd.next(branch_size)], A = H[c][branch_size];
            break;
        case QUERY::BRANCH_COMMON :
            c = rnd.any(H[0]);
            while(branch_root[c].size() < 2) c = rnd.any(H[0]);
            a = b = rnd.any(branch_root[c]);
            while(a == b) b = rnd.any(branch_root[c]);
            A = H[a][rnd.next(H[a].size() - 1)];
            B = H[b][rnd.next(H[b].size() - 1)];
            break;
        case QUERY::CYCLE_CYCLE :
            A = B = rnd.any(H[0]);
            while(A == B) B = rnd.any(H[0]);
            break;
        case QUERY::CYCLE_BRANCH :
            A = rnd.any(H[0]);
            c = rnd.next(1, branch_amount);
            while(H[c].back() == A) c = rnd.next(1, branch_amount);
            branch_size = H[c].size() - 1;
            B = H[c][rnd.next(branch_size)];
            break;
        case QUERY::BRANCH_CYCLE :
            B = rnd.any(H[0]);
            c = rnd.next(1, branch_amount);
            while(H[c].back() == B) c = rnd.next(1, branch_amount);
            branch_size = H[c].size() - 1;
            A = H[c][rnd.next(branch_size)];
            break;
        case QUERY::BRANCH_DIFF :
            a = b = rnd.next(1, branch_amount);
            while(H[a].back() == H[b].back()) b = rnd.next(1, branch_amount);
            A = H[a][rnd.next(H[a].size() - 1)];
            B = H[b][rnd.next(H[b].size() - 1)];
            break;
    }
    return {A, B};
}

void make_normal_testcase(int N, string case_name, bool is_cycle, QUERY query_type){
    auto [G, H] = make_pseudotree(N);
    auto [A, B] = make_query(H, query_type);
    while(A == -1 and B == -1){
        auto [TG, TH] = make_pseudotree(N);
        auto [TA, TB] = make_query(TH, query_type);
        G = TG, H = TH, A = TA, B = TB;
    }

    // for(int i = 0; i < H.size(); ++i){
    //     cerr << i << " ->";
    //     for(int j = 0; j < H[i].size(); ++j){
    //         cerr << " " << H[i][j];
    //     }
    //     cerr << endl;
    // }

    ofstream of(case_name.c_str());
    of << N << endl;
    for(auto [u, v] : G){
        of << u << " " << v << endl;
    }
    of << 1 << endl;
    of << A << " " << B << endl;
    of.close();
}

void make_hard_testcase(int N, int T, string case_name, bool is_cycle = false){
    auto [G, H] = make_pseudotree(N, is_cycle);

    ofstream of(case_name.c_str());
    of << N << endl;
    for(auto [u, v] : G){
        of << u << " " << v << endl;
    }
    of << T << endl;
    for(int t = 0; t < T; ++t){
        QUERY query = static_cast<QUERY>(rnd.next(static_cast<int>(QUERY::DUMMY)));
        auto [A, B] = make_query(H, query);
        while(A == -1){
            query = static_cast<QUERY>(rnd.next(static_cast<int>(QUERY::DUMMY)));
            auto [TA, TB] = make_query(H, query);
            A = TA, B = TB;
        }
        of << A << " " << B << endl;
    }
    of.close();
}

int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);

    // 00 sample
    make_sample_testcase();

    // 1* Easy
    for(int t = 1; t <= 5; ++t){
        make_easy_testcase(rnd.next(SMALL_MIN_N, SMALL_MAX_N), format("10_small_%02d.in", t));
    }
    for(int t = 1; t <= 5; ++t){
        make_easy_testcase(rnd.next(LARGE_MIN_N, LARGE_MAX_N), format("11_large_%02d.in", t));
    }
    for(int t = 1; t <= 3; ++t){
        make_easy_testcase(rnd.next(LARGE_MIN_N, LARGE_MAX_N), format("12_not_circle_branch_%02d.in", t), 0, 0);
    }
    for(int t = 1; t <= 3; ++t){
        make_easy_testcase(rnd.next(LARGE_MIN_N, LARGE_MAX_N), format("13_not_circle_circle_%02d.in", t), 0, 1);
    }
    for(int t = 1; t <= 3; ++t){
        make_easy_testcase(rnd.next(LARGE_MIN_N, LARGE_MAX_N), format("14_circle_circle_%02d.in", t), 1, 1);
    }
    for(int t = 1; t <= 5; ++t){
        make_easy_testcase(MAX_N, format("15_max_%02d.in", t));
    }
    {
        ofstream of("16_min_01.in");
        of << "3" << endl;
        of << "1 2" << endl;
        of << "2 3" << endl;
        of << "1 3" << endl;
        of << "1" << endl;
        of << "3 1" << endl;
        of.close();
    }
    {
        ofstream of("16_min_02.in");
        of << "3" << endl;
        of << "1 2" << endl;
        of << "2 3" << endl;
        of << "1 3" << endl;
        of << "1" << endl;
        of << "3 2" << endl;
        of.close();
    }

    // 2* normal
    vector<string> case_name{"branch_same", "branch_root", "root_branch", "branch_common", "cycle_cycle", "cycle_branch", "branch_cycle", "branch_diff"};
    for(int q = 0; q < static_cast<int>(QUERY::DUMMY); ++q){
        for(int t = 1; t <= 3; ++t){
            make_normal_testcase(rnd.next(LARGE_MIN_N, LARGE_MAX_N), format("2%d_%s_%02d.in", q + 1, case_name[q].c_str(), t), false, static_cast<QUERY>(q));
        }
    }
    for(int t = 1; t <= 10; ++t){
        make_normal_testcase(MAX_N, format("29_max_%02d.in", t), false, static_cast<QUERY>(rnd.next(static_cast<int>(QUERY::DUMMY))));
    }
    
    // 3* hard
    for(int t = 1; t <= 10; ++t){
        make_hard_testcase(rnd.next(LARGE_MIN_N, LARGE_MAX_N), rnd.next(LARGE_MIN_T, LARGE_MAX_T), format("30_random_%02d.in", t), true);
    }
    for(int t = 11; t <= 20; ++t){
        make_hard_testcase(rnd.next(LARGE_MIN_N, LARGE_MAX_N), rnd.next(LARGE_MIN_T, LARGE_MAX_T), format("30_random_%02d.in", t), true);
    }
    for(int t = 21; t <= 30; ++t){
        make_hard_testcase(MAX_N, MAX_T, format("30_random_%02d.in", t), true);
    }

    // make_normal_testcase(10, "test.in", false, QUERY::CYCLE_BRANCH);

    return 0;
}

// enum class QUERY{
//     BRANCH_SAME,
//     BRANCH_ROOT,
//     ROOT_BRANCH,
//     BRANCH_COMMON,
//     CYCLE_CYCLE,
//     CYCLE_BRANCH,
//     BRANCH_CYCLE,
//     BRANCH_DIFF,
//     DUMMY,
// };