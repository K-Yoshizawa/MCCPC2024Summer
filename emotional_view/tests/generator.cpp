#include <bits/stdc++.h>
#include "testlib.h"
#include "constrains.h"
using namespace std;

namespace delaunay {

struct Point {
    /*** Point on the 2D-plane ***/
    double x, y;
    Point operator + (const Point& p) const { return Point{x + p.x, y + p.y}; }
    Point operator - (const Point& p) const { return Point{x - p.x, y - p.y}; }
    Point operator * (double d) const { return Point{x * d, y * d}; }
    Point operator / (double d) const { return Point{x / d, y / d}; }
    bool operator < (const Point& p) const { return x == p.x ? y < p.y : x < p.x; }
    Point normal() const { return Point{y, -x}; }
    double norm() const { return x * x + y * y; }
};

double dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
double cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }

/*** Edge connecting two points ***/
using Edge = std::pair<size_t, size_t>;
Edge make_edge(size_t a, size_t b) { return Edge(std::min(a,b), std::max(a,b)); }
    
/*** Core Implementation ***/
class DelaunayTriangulation {
    bool is_ccw(size_t a, size_t b, size_t c) const { return cross(P[b] - P[a], P[c] - P[a]) > 0; }
    
    struct Triangle {
        /*** Triangle on the 2D-plane ***/
        size_t a, b, c;
        size_t opposite(Edge e) const {
            if (e.first != a and e.second != a) return a;
            if (e.first != b and e.second != b) return b;
            return c;
        }
    };
    
    Triangle make_triangle(size_t a, size_t b, size_t c) const {
        /*** Make triangle where the direction 'a->b->c' is counter-clockwise ***/
        if (!is_ccw(a, b, c)) std::swap(b, c);
        return Triangle{a, b, c};
    }
    
    bool point_in_triangle(size_t tar, const Triangle& t) const {
        /*** Check wheter a point lies in an triangle or not ***/
        if (!is_ccw(t.a, t.b, tar)) return false;
        if (!is_ccw(t.b, t.c, tar)) return false;
        if (!is_ccw(t.c, t.a, tar)) return false;
        return true;
    }
    
private:
    size_t n;
    std::vector<Point> P;
    std::vector<Triangle> T;
    std::vector<std::list<size_t>> CH;
    std::vector<Edge> edge;
    
    size_t add_child_triangle(size_t k, const Triangle& t) {
        /*** Add a child triangle for T[k] ***/
        size_t new_k = T.size();
        T.push_back(t);
        CH.push_back(std::list<size_t>());
        CH[k].push_back(new_k);
        return new_k;
    }
    
    size_t add_child_triangle(size_t k1, size_t k2, const Triangle& t) {
        /*** Add a child triangle for T[k1] and T[k2] ***/
        size_t new_k = T.size();
        T.push_back(t);
        CH.push_back(std::list<size_t>());
        CH[k1].push_back(new_k);
        CH[k2].push_back(new_k);
        return new_k;
    }
    
    size_t find_child(size_t k, size_t tar) const {
        /*** Find child triangle of T[k] where P[tar] lies in ***/
        for (size_t i : CH[k]) if (point_in_triangle(tar, T[i])) return i;
        return std::numeric_limits<size_t>::max();
    }
    
private:
    struct EdgeHash {
        /*** Hash function for edges ***/
        size_t operator () (const Edge& e) const {
            static const size_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
            size_t key = ((e.first << 16) ^ e.second) ^ FIXED_RANDOM;
            return key ^ (key >> 16);
        }
    };
    
    // Maps an edge to its incident triangles
    std::unordered_map<Edge, std::set<size_t>, EdgeHash> e2t;
    
    void register_triangle(size_t k, const Triangle& t) {
        /*** Register a new triangle ***/
        e2t[make_edge(t.a, t.b)].insert(k);
        e2t[make_edge(t.b, t.c)].insert(k);
        e2t[make_edge(t.c, t.a)].insert(k);
    }
    
    void unregister_triangle(size_t k, const Triangle& t) {
        /*** Unregister an old triangle ***/
        e2t[make_edge(t.a, t.b)].erase(k);
        e2t[make_edge(t.b, t.c)].erase(k);
        e2t[make_edge(t.c, t.a)].erase(k);
    }
    
private:
    bool is_ilegal(Edge e, size_t c, size_t tar) {
        /*** Check wheter an edge is ilegal or not ***/
        size_t a = e.first, b = e.second;
        
        Point s1 = (P[a] + P[b]) / 2.;
        Point s2 = (P[b] + P[c]) / 2.;
        Point t1 = s1 + (P[b] - P[a]).normal();
        Point t2 = s2 + (P[c] - P[b]).normal();
        
        double d1 = cross(t2 - s2, s2 - s1);
        double d2 = cross(t2 - s2, t1 - s1);
        Point ct = s1 + (t1 - s1) * d1 / d2;
        
        double dx1 = P[a].x - ct.x;
        double dy1 = P[a].y - ct.y;
        double dx2 = P[tar].x - ct.x;
        double dy2 = P[tar].y - ct.y;
        return (dx1 * dx1 + dy1 * dy1) > (dx2 * dx2 + dy2 * dy2);
    }
    
    void legalize_edge(size_t piv, Edge e) {
        /*** Legalize an edge with pivot P[piv] ***/
        if (e2t.count(e) == 0) return;
        if (e2t[e].size() != 2) return;
        
        size_t k1 = *e2t[e].begin();
        size_t k2 = *e2t[e].rbegin();
        size_t a = T[k1].opposite(e);
        size_t b = T[k2].opposite(e);
                
        if (is_ilegal(e, a, b)) {
            unregister_triangle(k1, T[k1]);
            unregister_triangle(k2, T[k2]);
            e2t.erase(e);
            
            Triangle t1 = make_triangle(e.first, a, b);
            Triangle t2 = make_triangle(e.second, a, b);
            
            size_t k1_ = add_child_triangle(k1, k2, t1);
            size_t k2_ = add_child_triangle(k1, k2, t2);
            
            register_triangle(k1_, t1);
            register_triangle(k2_, t2);
            
            size_t c = (piv != a ? a : b);
            legalize_edge(piv, make_edge(e.first, c));
            legalize_edge(piv, make_edge(e.second, c));
        }
    }
    
    void sub_division(size_t k, size_t tar) {
        /*** Divide triangle T[k] by P[tar] ***/
        unregister_triangle(k, T[k]);
        
        Triangle t1 = make_triangle(T[k].a, T[k].b, tar);
        Triangle t2 = make_triangle(T[k].b, T[k].c, tar);
        Triangle t3 = make_triangle(T[k].c, T[k].a, tar);
        
        size_t k1 = add_child_triangle(k, t1);
        size_t k2 = add_child_triangle(k, t2);
        size_t k3 = add_child_triangle(k, t3);
        
        register_triangle(k1, t1);
        register_triangle(k2, t2);
        register_triangle(k3, t3);
        
        legalize_edge(tar, make_edge(T[k].a, T[k].b));
        legalize_edge(tar, make_edge(T[k].b, T[k].c));
        legalize_edge(tar, make_edge(T[k].c, T[k].a));
    }
    
    void modify_convexity() {
        /*** Modify edges of the bounding convex hull ***/
        for (size_t a=n; a<=n+2; ++a) {
            for (size_t b=0; b<n; ++b) {
                Edge e(b, a);
                if (e2t.count(e) == 0) continue;
                
                size_t k1 = *e2t[e].begin();
                size_t k2 = *e2t[e].rbegin();
                
                size_t c = T[k1].opposite(e);
                size_t d = T[k2].opposite(e);
                
                if (!is_ccw(a, b, c)) std::swap(c, d);
                if (!is_ccw(c, d, b)) continue;
                
                unregister_triangle(k1, T[k1]);
                unregister_triangle(k2, T[k2]);
                
                Triangle t1 = make_triangle(a, c, d);
                Triangle t2 = make_triangle(b, c, d);
                
                size_t k1_ = add_child_triangle(k1, k2, t1);
                size_t k2_ = add_child_triangle(k1, k2, t2);
                
                register_triangle(k1_, t1);
                register_triangle(k2_, t2);
            }
        }
    }
    
private:
    std::uint32_t seed;
    
    std::uint32_t xor128() {
        static std::uint32_t x = seed, y = 362436069, z = 521288629, w = 88675123;
        std::uint32_t t = (x ^ (x << 11));
        x = y; y = z; z = w;
        return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
    }
    
public:
    DelaunayTriangulation(const std::vector<double>& x, const std::vector<double>& y, uint32_t seed_ = 123456789) {
        n = x.size();
        P = std::vector<Point>(n);
        for (size_t i=0; i<n; ++i) {
            P[i].x = x[i];
            P[i].y = y[i];
        }
        
        double r = std::numeric_limits<double>::min();
        for (size_t i=0; i<n; ++i) {
            r = std::max(r, std::abs(P[i].x));
            r = std::max(r, std::abs(P[i].y));
        }
        
        // Add three vertices of the initial bounding triangle
        P.push_back(Point{3.1 * r, 0});
        P.push_back(Point{0, 3.1 * r});
        P.push_back(Point{-3.1 * r, -3.1 * r});
        
        seed = seed_;
    }
    
    void execute(double min_delta = 1e-6, double max_delta = 1e-5, int max_miss_count = 30) {
        /*** Execute the algorithm ***/
        
        // Random reordering
        std::vector<size_t> id(n);
        std::iota(id.begin(), id.end(), size_t(0));
        for (size_t i=0; i<n; ++i) {
            size_t j = xor128() % (n - i);
            std::swap(id[j], id[n - i - 1]);
        }
        
        // Initialize each data structure
        T = std::vector<Triangle>();
        CH = std::vector<std::list<size_t>>();
        T.push_back(make_triangle(n, n+1, n+2));
        CH.push_back(std::list<size_t>());
        register_triangle(0, T[0]);
        e2t = std::unordered_map<Edge, std::set<size_t>, EdgeHash>();
        
        // Main iteration
        for (size_t tar : id) {
            int miss_count = 0;
            double px = P[tar].x, py = P[tar].y;
            size_t k = 0;
            while (!CH[k].empty()) {
                size_t nxt = find_child(k, tar);
                if (nxt == std::numeric_limits<size_t>::max()) {
                    ++miss_count;
                    if (miss_count >= max_miss_count) break;
                    // P[tar] perturbates when it falls on an edge
                    double dx = min_delta + (max_delta - min_delta) * xor128() / 0xFFFFFFFFu;
                    double dy = min_delta + (max_delta - min_delta) * xor128() / 0xFFFFFFFFu;
                    dx *= (xor128() % 2 == 0 ? 1 : -1);
                    dy *= (xor128() % 2 == 0 ? 1 : -1);
                    P[tar].x = px + dx;
                    P[tar].y = py + dy;
                }
                else {
                    k = nxt;
                }
            }
            if (CH[k].empty()) sub_division(k, tar);
            P[tar].x = px;
            P[tar].y = py;
        }
        
        // Modify edges of the bounding convex hull
        modify_convexity();
        
        // Save the solution
        edge = std::vector<Edge>();
        for (auto it : e2t) {
            Edge e = it.first;
            if (e.first < n and e.second < n) edge.push_back(e);
        }
    }
    
    const std::vector<Edge>& get_edges() { return edge; }
    
    void dump(std::ostream& os) {
        os << edge.size() << std::endl;
        for (Edge e : edge) os << e.first << " " << e.second << std::endl;
    }
};

}

void make_sample_testcase(){
    {
        ofstream of("00_sample_01.in");
        of << "5" << endl;
        of << "4 0 1" << endl;
        of << "5 -5 1" << endl;
        of << "3 3 1" << endl;
        of << "3 -3 1" << endl;
        of << "5 5 1" << endl;
        of.close();
    }
    {
        ofstream of("00_sample_02.in");
        of << "10" << endl;
        of << "7 -1 1" << endl;
        of << "15 7 4" << endl;
        of << "7 -12 2" << endl;
        of << "4 -5 3" << endl;
        of << "12 -6 1" << endl;
        of << "4 10 1" << endl;
        of << "9 -5 2" << endl;
        of << "3 7 2" << endl;
        of << "4 -1 1" << endl;
        of << "9 0 1" << endl;
        of.close();
    }
    {
        ofstream of("00_sample_03.in");
        of << "10" << endl;
        of << "15 12 4" << endl;
        of << "3 -13 2" << endl;
        of << "-1 -19 5" << endl;
        of << "7 17 4" << endl;
        of << "-13 -10 2" << endl;
        of << "18 4 2" << endl;
        of << "-9 8 4" << endl;
        of << "-12 18 6" << endl;
        of << "1 3 2" << endl;
        of << "3 7 1" << endl;
        of.close();
    }
}

void make_easy_testcase(int N, string case_name){
    vector<int> x(N), y(N), r(N, 1);
    set<pair<int, int>> point_set;
    int dx[] = {1, 1, 0, -1, -1, -1, 0, 1};
    int dy[] = {0, -1, -1, -1, 0, 1, 1, 1};
    auto check = [&](int tmp_x, int tmp_y) -> bool {
        if(abs(tmp_x) + abs(tmp_y) <= 1) return false;
        if(point_set.count({tmp_x, tmp_y})) return false;
        for(int delta = 0; delta < 8; ++delta){
            int cur_x = tmp_x + dx[delta];
            int cur_y = tmp_y + dy[delta];
            if(point_set.count({cur_x, cur_y})) return false;
        }
        return true;
    };
    for(int i = 0; i < N; ++i){
        int cand_x = rnd.next(EASY_MIN_X, EASY_MAX_X);
        int cand_y = rnd.next(-1, 1) * cand_x;
        while(1){
            if(check(cand_x, cand_y)) break;
            cand_x = rnd.next(EASY_MIN_X, EASY_MAX_X);
            cand_y = rnd.next(-1, 1) * cand_x;
        }
        x[i] = cand_x, y[i] = cand_y;
        point_set.emplace(cand_x, cand_y);
    }
    ofstream of(case_name.c_str());
    of << N << endl;
    for(int i = 0; i < N; ++i){
        of << x[i] << " " << y[i] << " " << r[i] << endl;
    }
    of.close();
}

void make_normal_testcase(int N, string case_name, int LIM_r = 2 * MAX_XY){
    vector<int> x(N), y(N), r(N, 0);
    vector<double> delaunay_x, delaunay_y;
    set<pair<int, int>> point_set;
    int dx[] = {1, 1, 0, -1, -1, -1, 0, 1};
    int dy[] = {0, -1, -1, -1, 0, 1, 1, 1};
    auto check = [&](int tmp_x, int tmp_y) -> bool {
        if(abs(tmp_x) + abs(tmp_y) <= 1) return false;
        if(point_set.count({tmp_x, tmp_y})) return false;
        for(int delta = 0; delta < 8; ++delta){
            int cur_x = tmp_x + dx[delta];
            int cur_y = tmp_y + dy[delta];
            if(point_set.count({cur_x, cur_y})) return false;
        }
        return true;
    };
    for(int i = 0; i < N; ++i){
        int cand_x = rnd.next(NORMAL_MIN_X, NORMAL_MAX_X);
        int cand_y = rnd.next(NORMAL_MIN_Y, NORMAL_MAX_Y);
        while(1){
            if(check(cand_x, cand_y)) break;
            cand_x = rnd.next(NORMAL_MIN_X, NORMAL_MAX_X);
            cand_y = rnd.next(NORMAL_MIN_Y, NORMAL_MAX_Y);
        }
        x[i] = cand_x, y[i] = cand_y;
        point_set.emplace(cand_x, cand_y);
        delaunay_x.push_back(static_cast<double>(cand_x));
        delaunay_y.push_back(static_cast<double>(cand_y));
    }
    delaunay::DelaunayTriangulation DT(delaunay_x, delaunay_y);
    DT.execute();
    vector<delaunay::Edge> result_edge = DT.get_edges();
    auto dist = [&](int i, int j) -> int {
        double dx = delaunay_x[i] - delaunay_x[j];
        double dy = delaunay_y[i] - delaunay_y[j];
        return (int)sqrt(dx * dx + dy * dy);
    };
    vector<vector<pair<int, int>>> G(N);
    for(auto [i, j] : result_edge){
        G[i].emplace_back(j, dist(i, j));
        G[j].emplace_back(i, dist(i, j));
    }
    vector<int> order(N);
    iota(order.begin(), order.end(), 0);
    shuffle(order.begin(), order.end());
    for(auto i : order){
        int MAX_R = min({x[i] - 1, LIM_r, (int)sqrt(delaunay_x[i] * delaunay_x[i] + delaunay_y[i] * delaunay_y[i])});
        for(auto [j, d] : G[i]){
            MAX_R = min(MAX_R, min(d - r[j], d - 1));
        }
        r[i] = rnd.next(1, MAX_R);
    }
    ofstream of(case_name.c_str());
    of << N << endl;
    for(int i = 0; i < N; ++i){
        of << x[i] << " " << y[i] << " " << r[i] << endl;
    }
    of.close();
}

void make_hard_testcase(int N, string case_name, int LIM_r = 2 * MAX_XY){
    vector<int> x(N), y(N), r(N, 0);
    vector<double> delaunay_x, delaunay_y;
    set<pair<int, int>> point_set;
    int dx[] = {1, 1, 0, -1, -1, -1, 0, 1};
    int dy[] = {0, -1, -1, -1, 0, 1, 1, 1};
    auto check = [&](int tmp_x, int tmp_y) -> bool {
        if(abs(tmp_x) + abs(tmp_y) <= 1) return false;
        if(point_set.count({tmp_x, tmp_y})) return false;
        for(int delta = 0; delta < 8; ++delta){
            int cur_x = tmp_x + dx[delta];
            int cur_y = tmp_y + dy[delta];
            if(point_set.count({cur_x, cur_y})) return false;
        }
        return true;
    };
    for(int i = 0; i < N; ++i){
        int cand_x = rnd.next(MIN_XY, MAX_XY);
        int cand_y = rnd.next(MIN_XY, MAX_XY);
        while(1){
            if(check(cand_x, cand_y)) break;
            cand_x = rnd.next(MIN_XY, MAX_XY);
            cand_y = rnd.next(MIN_XY, MAX_XY);
        }
        x[i] = cand_x, y[i] = cand_y;
        point_set.emplace(cand_x, cand_y);
        delaunay_x.push_back(static_cast<double>(cand_x));
        delaunay_y.push_back(static_cast<double>(cand_y));
    }
    delaunay::DelaunayTriangulation DT(delaunay_x, delaunay_y);
    DT.execute();
    vector<delaunay::Edge> result_edge = DT.get_edges();
    auto dist = [&](int i, int j) -> int {
        double dx = delaunay_x[i] - delaunay_x[j];
        double dy = delaunay_y[i] - delaunay_y[j];
        return (int)sqrt(dx * dx + dy * dy);
    };
    vector<vector<pair<int, int>>> G(N);
    for(auto [i, j] : result_edge){
        G[i].emplace_back(j, dist(i, j));
        G[j].emplace_back(i, dist(i, j));
    }
    vector<int> order(N);
    iota(order.begin(), order.end(), 0);
    shuffle(order.begin(), order.end());
    for(auto i : order){
        int MAX_R = min(LIM_r, (int)sqrt(delaunay_x[i] * delaunay_x[i] + delaunay_y[i] * delaunay_y[i]));
        for(auto [j, d] : G[i]){
            MAX_R = min(MAX_R, min(d - r[j], d - 1));
        }
        r[i] = rnd.next(1, MAX_R);
    }
    ofstream of(case_name.c_str());
    of << N << endl;
    for(int i = 0; i < N; ++i){
        of << x[i] << " " << y[i] << " " << r[i] << endl;
    }
    of.close();
}

void make_maximum_testcase(int N, string case_name, int LIM_r = 2 * MAX_XY){
    vector<int> x(N), y(N), r(N, 0);
    vector<double> delaunay_x, delaunay_y;
    set<pair<int, int>> point_set;
    int dx[] = {1, 1, 0, -1, -1, -1, 0, 1};
    int dy[] = {0, -1, -1, -1, 0, 1, 1, 1};
    auto check = [&](int tmp_x, int tmp_y) -> bool {
        if(abs(tmp_x) + abs(tmp_y) <= 1) return false;
        if(point_set.count({tmp_x, tmp_y})) return false;
        for(int delta = 0; delta < 8; ++delta){
            int cur_x = tmp_x + dx[delta];
            int cur_y = tmp_y + dy[delta];
            if(point_set.count({cur_x, cur_y})) return false;
        }
        return true;
    };
    for(int i = 0; i < N; ++i){
        int cand_x = rnd.next(MIN_XY, MAX_XY);
        int cand_y = rnd.next(MIN_XY, MAX_XY);
        while(1){
            if(check(cand_x, cand_y)) break;
            cand_x = rnd.next(MIN_XY, MAX_XY);
            cand_y = rnd.next(MIN_XY, MAX_XY);
        }
        x[i] = cand_x, y[i] = cand_y;
        point_set.emplace(cand_x, cand_y);
        delaunay_x.push_back(static_cast<double>(cand_x));
        delaunay_y.push_back(static_cast<double>(cand_y));
    }
    delaunay::DelaunayTriangulation DT(delaunay_x, delaunay_y);
    DT.execute();
    vector<delaunay::Edge> result_edge = DT.get_edges();
    auto dist = [&](int i, int j) -> int {
        double dx = delaunay_x[i] - delaunay_x[j];
        double dy = delaunay_y[i] - delaunay_y[j];
        return (int)sqrt(dx * dx + dy * dy);
    };
    vector<vector<pair<int, int>>> G(N);
    for(auto [i, j] : result_edge){
        G[i].emplace_back(j, dist(i, j));
        G[j].emplace_back(i, dist(i, j));
    }
    vector<int> order(N);
    iota(order.begin(), order.end(), 0);
    shuffle(order.begin(), order.end());
    for(auto i : order){
        int MAX_R = min(LIM_r, (int)sqrt(delaunay_x[i] * delaunay_x[i] + delaunay_y[i] * delaunay_y[i]));
        for(auto [j, d] : G[i]){
            MAX_R = min(MAX_R, min(d - r[j], d - 1));
        }
        // r[i] = rnd.next(1, MAX_R);
        r[i] = MAX_R;
    }
    ofstream of(case_name.c_str());
    of << N << endl;
    for(int i = 0; i < N; ++i){
        of << x[i] << " " << y[i] << " " << r[i] << endl;
    }
    of.close();
}

int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);

    // // 00 sample
    // make_sample_testcase();

    // // 1* Easy
    // for(int t = 1; t <= 10; ++t){
    //     make_easy_testcase(rnd.next(EASY_RND_MIN_N, EASY_RND_MAX_N), format("10_random_%02d.in", t));
    // }
    // for(int t = 1; t <= 5; ++t){
    //     make_easy_testcase(EASY_MAX_N, format("11_max_%02d.in", t));
    // }
    
    // // 2* Normal
    // for(int t = 1; t <= 10; ++t){
    //     make_normal_testcase(rnd.next(NORMAL_SMALL_MIN_N, NORMAL_SMALL_MAX_N), format("20_small_%02d.in", t));
    // }
    // for(int t = 1; t <= 10; ++t){
    //     make_normal_testcase(rnd.next(NORMAL_SMALL_MIN_N, NORMAL_SMALL_MAX_N), format("21_large_%02d.in", t));
    // }
    // for(int t = 1; t <= 5; ++t){
    //     make_normal_testcase(NORMAL_MAX_N, format("22_max_%02d.in", t));
    // }
    // for(int t = 1; t <= 5; ++t){
    //     make_normal_testcase(NORMAL_MAX_N, format("23_tiny_%02d.in", t), 1);
    // }

    // 3* hard
    // for(int t = 1; t <= 10; ++t){
    //     make_hard_testcase(rnd.next(HARD_SMALL_MIN_N, HARD_SMALL_MAX_N), format("30_small_%02d.in", t));
    // }
    // for(int t = 1; t <= 10; ++t){
    //     make_hard_testcase(rnd.next(HARD_MEDIUM_MIN_N, HARD_MEDIUM_MAX_N), format("31_medium_%02d.in", t));
    // }
    // for(int t = 1; t <= 10; ++t){
    //     make_hard_testcase(rnd.next(HARD_LARGE_MIN_N, HARD_LARGE_MAX_N), format("32_large_%02d.in", t));
    // }
    for(int t = 1; t <= 50; ++t){
        make_hard_testcase(MAX_N, format("33_max_%02d.in", t));
    }
    for(int t = 1; t <= 50; ++t){
        make_maximum_testcase(MAX_N, format("35_maximum_%02d.in", t));
    }
    for(int t = 1; t <= 50; ++t){
        make_hard_testcase(MAX_N, format("34_tiny_%02d.in", t), 1);
    }
    // {
    //     ofstream of("39_hand_01.in");
    //     of << "4" << endl;
    //     of << "1 2 1" << endl;
    //     of << "50000 100000 50000" << endl;
    //     of << "50000 -2 1" << endl;
    //     of << "100000 -4 2" << endl;
    //     of.close();
    // }
    // {
    //     ofstream of("39_hand_02.in");
    //     of << "4" << endl;
    //     of << "1 2 1" << endl;
    //     of << "-50000 100000 50000" << endl;
    //     of << "100000 1 1" << endl;
    //     of << "2 -1 1" << endl;
    //     of.close();
    // }
    // {
    //     ofstream of("39_hand_03.in");
    //     of << "4" << endl;
    //     of << "0 9985 6943" << endl;
    //     of << "99912 42354 42354" << endl;
    //     of << "0 -5 3" << endl;
    //     of << "100000 -50000 50000" << endl;
    //     of.close();
    // }


    // make_easy_testcase(5, "90_random_01.in");

    return 0;
}