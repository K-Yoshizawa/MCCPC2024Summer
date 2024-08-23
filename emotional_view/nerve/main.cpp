#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using vl = vector<ll>;
template<class T> using vc = vector<T>;
template<class T> using vvc = vector<vector<T>>;

#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define rep(i, n) for (ll i = 0; i < (n); i++)
#define repr(i, n) for (ll i = (n)-1; i >= 0; i--)
#define repe(i, l, r) for (ll i = (l); i < (r); i++)
#define reper(i, l, r) for (ll i = (r)-1; i >= (l); i--)
#define repa(i,n) for (auto& i: n)

template<class T1, class T2> inline bool chmax(T1 &a, const T2 &b) {if (a<b) { a=b; return 1;} return 0;}
template<class T1, class T2> inline bool chmin(T1 &a, const T2 &b) {if (b<a) { a=b; return 1;} return 0;}

struct init{init(){cin.tie(0);ios::sync_with_stdio(false);cout<<fixed<<setprecision(15);cerr<<fixed<<setprecision(15);}}init_;

template <typename T, typename U> ostream& operator<<(ostream&out,const pair<T, U>&a){return out<<a.first<<' '<<a.second;}
template <typename T> ostream& operator<<(ostream&out, const vector<T>&a){for(auto it=a.begin();it!= a.end();){out<<*it;if(++it!=a.end())out<<' ';}return out;}
template <typename T, size_t N> ostream& operator<<(ostream&out, const array<T, N>&a){for(auto it=a.begin();it!= a.end();){out<<*it;if(++it!=a.end())out<<' ';}return out;}
template <typename T> ostream& operator<<(ostream&out, const set<T>&a){for(auto it=a.begin();it!=a.end();){out<<*it;if(++it!=a.end())out<<' ';}return out;}
template <typename T, typename U> ostream& operator<<(ostream&out, const map<T, U>&a){for(auto it=a.begin();it!=a.end();){out<<*it;if(++it!=a.end())out<<'\n';}return out;}

#ifdef DEBUG
template <class T, class N> void verr(const vector<T>& a, const N& n) { rep(i, n) cerr << a[i] << " "; cerr << endl; }
template <class T, class N, size_t AN> void verr(const array<T, AN>& a, const N& n) { rep(i, n) cerr << a[i] << " "; cerr << endl; }
ll dbgt = 1; void err() { cerr << "passed " << dbgt++ << endl; }
template<class H, class... T> void err(H&& h,T&&... t){ cerr<< h << (sizeof...(t)?" ":"\n") << flush; if(sizeof...(t)>0) err(forward<T>(t)...); }
#else
void err(){}
template <class H, class... T>
void err(H &&h, T &&...t) {}
template <class H, class... T>
void verr(H &&h, T &&...t) {}
#endif

const ll INF = 4e18;
const ld EPS = 1e-9;
const ld PI = acos(-1.0L);
// const ll MOD = 1e9 + 7;
const ll MOD = 998244353;
//--------------------------------------------------------------------------------//

using Real = long double;
using Point = complex<Real>;

inline int sign(const Real &r) {
    return r < -EPS ? -1 : (r > EPS ? 1 : 0);
}

inline bool equals(const Real &a, const Real &b) {
    return sign(a - b) == 0;
}

inline bool equals(const Point &a, const Point &b) {
    return equals(real(a), real(b)) && equals(imag(a), imag(b));
}

Point operator*(const Point &p, const Real &d) {
    return Point(real(p) * d, imag(p) * d);
}

istream &operator>>(istream &is, Point &p) {
    Real a, b;
    is >> a >> b;
    p = Point(a, b);
    return is;
}

ostream &operator<<(ostream &os, Point &p) {
    return os << fixed << setprecision(10) << p.real() << " " << p.imag();
}

// 点 p を反時計回りに theta 回転
Point rotate(const Point &p, Real theta) {
    return Point(cos(theta) * p.real() - sin(theta) * p.imag(), sin(theta) * p.real() + cos(theta) * p.imag());
}

Real radian_to_degree(Real r) {
    return (r * 180.0 / PI);
}

Real degree_to_radian(Real d) {
    return (d * PI / 180.0);
}

// a-b-c の角度のうち小さい方を返す
Real get_angle(const Point &a, const Point &b, const Point &c) {
    const Point v(b - a), w(c - b);
    Real alpha = atan2(v.imag(), v.real()), beta = atan2(w.imag(), w.real());
    if (alpha > beta) swap(alpha, beta);
    Real theta = (beta - alpha);
    return min(theta, 2 * acos(-1) - theta);
}

bool compare_x(const Point &a, const Point &b) {
    return equals(real(a), real(b)) ? imag(a) < imag(b) : real(a) < real(b);
}

bool compare_y(const Point &a, const Point &b) {
    return equals(imag(a), imag(b)) ? real(a) < real(b) : imag(a) < imag(b);
}

// 直線
struct Line {
    Point a, b;

    Line() = default;

    Line(Point a, Point b) : a(a), b(b) {}

    Line(Real A, Real B, Real C) // Ax + By = C
    {
        if (equals(A, 0))
            a = Point(0, C / B), b = Point(1, C / B);
        else if (equals(B, 0))
            b = Point(C / A, 0), b = Point(C / A, 1);
        else
            a = Point(0, C / B), b = Point(C / A, 0);
    }

    friend ostream &operator<<(ostream &os, Line &p) {
        return os << p.a << " to " << p.b;
    }

    friend istream &operator>>(istream &is, Line &a) {
        return is >> a.a >> a.b;
    }
};

// 線分
struct Segment : Line {
    Segment() = default;

    Segment(Point a, Point b) : Line(a, b) {}
};

struct Circle {
    Point p;
    Real r;

    Circle() = default;

    Circle(Point p, Real r) : p(p), r(r) {}
};

using Points = vector<Point>;
using Polygon = vector<Point>;
using Segments = vector<Segment>;
using Lines = vector<Line>;
using Circles = vector<Circle>;

Real cross(const Point &a, const Point &b) {
    return real(a) * imag(b) - imag(a) * real(b);
}

Real dot(const Point &a, const Point &b) {
    return real(a) * real(b) + imag(a) * imag(b);
}

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/1/CGL_1_C
// 点の回転方向
// 反時計回り: 1, 時計回り: -1, 同一直線上の後ろ: 2, 同一直線上の先: -2, 線分上: 0
int ccw(const Point &a, Point b, Point c) {
    b = b - a, c = c - a;
    if (cross(b, c) > EPS) return +1;  // "COUNTER_CLOCKWISE"
    if (cross(b, c) < -EPS) return -1; // "CLOCKWISE"
    if (dot(b, c) < 0) return +2;      // "ONLINE_BACK"
    if (norm(b) < norm(c)) return -2;  // "ONLINE_FRONT"
    return 0;                          // "ON_SEGMENT"
}

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/2/CGL_2_A
// 平行判定
bool parallel(const Line &a, const Line &b) {
    return equals(cross(a.b - a.a, b.b - b.a), 0.0);
}

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/2/CGL_2_A
// 垂直判定
bool orthogonal(const Line &a, const Line &b) {
    return equals(dot(a.a - a.b, b.a - b.b), 0.0);
}

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/1/CGL_1_A
// 射影
// 直線 l に p から垂線を引いた交点を求める
Point projection(const Line &l, const Point &p) {
    double t = dot(p - l.a, l.a - l.b) / norm(l.a - l.b);
    return l.a + (l.a - l.b) * t;
}

Point projection(const Segment &l, const Point &p) {
    double t = dot(p - l.a, l.a - l.b) / norm(l.a - l.b);
    return l.a + (l.a - l.b) * t;
}

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/1/CGL_1_B
// 反射
// 直線 l を対称軸として点 p  と線対称にある点を求める
Point reflection(const Line &l, const Point &p) {
    return p + (projection(l, p) - p) * 2.0;
}

bool intersect(const Line &l, const Point &p) {
    return abs(ccw(l.a, l.b, p)) != 1;
}

bool intersect(const Line &l, const Line &m) {
    return abs(cross(l.b - l.a, m.b - m.a)) > EPS || abs(cross(l.b - l.a, m.b - l.a)) < EPS;
}

bool intersect(const Segment &s, const Point &p) {
    return ccw(s.a, s.b, p) == 0;
}

bool intersect(const Line &l, const Segment &s) {
    return cross(l.b - l.a, s.a - l.a) * cross(l.b - l.a, s.b - l.a) < EPS;
}

Real distance(const Line &l, const Point &p);

bool intersect(const Circle &c, const Line &l) {
    return distance(l, c.p) <= c.r + EPS;
}

bool intersect(const Circle &c, const Point &p) {
    return abs(abs(p - c.p) - c.r) < EPS;
}

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/2/CGL_2_B
bool intersect(const Segment &s, const Segment &t) {
    return ccw(s.a, s.b, t.a) * ccw(s.a, s.b, t.b) <= 0 && ccw(t.a, t.b, s.a) * ccw(t.a, t.b, s.b) <= 0;
}

int intersect(const Circle &c, const Segment &l) {
    if (norm(projection(l, c.p) - c.p) - c.r * c.r > EPS) return 0;
    auto d1 = abs(c.p - l.a), d2 = abs(c.p - l.b);
    if (d1 < c.r + EPS && d2 < c.r + EPS) return 0;
    if (d1 < c.r - EPS && d2 > c.r + EPS || d1 > c.r + EPS && d2 < c.r - EPS) return 1;
    const Point h = projection(l, c.p);
    if (dot(l.a - h, l.b - h) < 0) return 2;
    return 0;
}

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/7/CGL_7_A
int intersect(Circle c1, Circle c2) {
    if (c1.r < c2.r) swap(c1, c2);
    Real d = abs(c1.p - c2.p);
    if (c1.r + c2.r < d) return 4;
    if (equals(c1.r + c2.r, d)) return 3;
    if (c1.r - c2.r < d) return 2;
    if (equals(c1.r - c2.r, d)) return 1;
    return 0;
}

Real distance(const Point &a, const Point &b) {
    return abs(a - b);
}

Real distance(const Line &l, const Point &p) {
    return abs(p - projection(l, p));
}

Real distance(const Line &l, const Line &m) {
    return intersect(l, m) ? 0 : distance(l, m.a);
}

Real distance(const Segment &s, const Point &p) {
    Point r = projection(s, p);
    if (intersect(s, r)) return abs(r - p);
    return min(abs(s.a - p), abs(s.b - p));
}

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/2/CGL_2_D
Real distance(const Segment &a, const Segment &b) {
    if (intersect(a, b)) return 0;
    return min({distance(a, b.a), distance(a, b.b), distance(b, a.a), distance(b, a.b)});
}

Real distance(const Line &l, const Segment &s) {
    if (intersect(l, s)) return 0;
    return min(distance(l, s.a), distance(l, s.b));
}

Point crosspoint(const Line &l, const Line &m) {
    Real A = cross(l.b - l.a, m.b - m.a);
    Real B = cross(l.b - l.a, l.b - m.a);
    if (equals(abs(A), 0.0) && equals(abs(B), 0.0)) return m.a;
    return m.a + (m.b - m.a) * B / A;
}

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/2/CGL_2_C
Point crosspoint(const Segment &l, const Segment &m) {
    return crosspoint(Line(l), Line(m));
}

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/7/CGL_7_D
pair<Point, Point> crosspoint(const Circle &c, const Line l) {
    Point pr = projection(l, c.p);
    Point e = (l.b - l.a) / abs(l.b - l.a);
    if (equals(distance(l, c.p), c.r)) return {pr, pr};
    double base = sqrt(c.r * c.r - norm(pr - c.p));
    return {pr - e * base, pr + e * base};
}

pair<Point, Point> crosspoint(const Circle &c, const Segment &l) {
    Line aa = Line(l.a, l.b);
    if (intersect(c, l) == 2) return crosspoint(c, aa);
    auto ret = crosspoint(c, aa);
    if (dot(l.a - ret.first, l.b - ret.first) < 0)
        ret.second = ret.first;
    else
        ret.first = ret.second;
    return ret;
}

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/7/CGL_7_E
pair<Point, Point> crosspoint(const Circle &c1, const Circle &c2) {
    Real d = abs(c1.p - c2.p);
    Real a = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d));
    Real t = atan2(c2.p.imag() - c1.p.imag(), c2.p.real() - c1.p.real());
    Point p1 = c1.p + Point(cos(t + a) * c1.r, sin(t + a) * c1.r);
    Point p2 = c1.p + Point(cos(t - a) * c1.r, sin(t - a) * c1.r);
    return {p1, p2};
}

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/7/CGL_7_F
// 点 p を通る円 c の接線
pair<Point, Point> tangent(const Circle &c1, const Point &p2) {
    return crosspoint(c1, Circle(p2, sqrt(norm(c1.p - p2) - c1.r * c1.r)));
}

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/7/CGL_7_G
// 円 c1, c2 の共通接線
Lines tangent(Circle c1, Circle c2) {
    Lines ret;
    if (c1.r < c2.r) swap(c1, c2);
    Real g = norm(c1.p - c2.p);
    if (equals(g, 0)) return ret;
    Point u = (c2.p - c1.p) / sqrt(g);
    Point v = rotate(u, PI * 0.5);
    for (int s : {-1, 1}) {
        Real h = (c1.r + s * c2.r) / sqrt(g);
        if (equals(1 - h * h, 0)) {
            ret.emplace_back(c1.p + u * c1.r, c1.p + (u + v) * c1.r);
        } else if (1 - h * h > 0) {
            Point uu = u * h, vv = v * sqrt(1 - h * h);
            ret.emplace_back(c1.p + (uu + vv) * c1.r, c2.p - (uu + vv) * c2.r * s);
            ret.emplace_back(c1.p + (uu - vv) * c1.r, c2.p - (uu - vv) * c2.r * s);
        }
    }
    return ret;
}

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/3/CGL_3_B
// 凸性判定
bool is_convex(const Polygon &p) {
    int n = (int)p.size();
    for (int i = 0; i < n; i++) {
        if (ccw(p[(i + n - 1) % n], p[i], p[(i + 1) % n]) == -1) return false;
    }
    return true;
}

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/4/CGL_4_A
// 凸包
Polygon convex_hull(Polygon &p) {
    int n = (int)p.size(), k = 0;
    if (n <= 2) return p;
    sort(p.begin(), p.end(), compare_x);
    vector<Point> ch(2 * n);
    auto check = [&](int i) {
        return sign(cross(ch[k - 1] - ch[k - 2], p[i] - ch[k - 1])) <= -1;
    };
    for (int i = 0; i < n; ch[k++] = p[i++]) {
        while (k >= 2 && check(i)) --k;
    }
    for (int i = n - 2, t = k + 1; i >= 0; ch[k++] = p[i--]) {
        while (k >= t && check(i)) --k;
    }
    ch.resize(k - 1);
    return ch;
}

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/3/CGL_3_C
// 多角形と点の包含判定
enum {
    OUT,
    ON,
    IN
};

int contains(const Polygon &Q, const Point &p) {
    bool in = false;
    for (int i = 0; i < Q.size(); i++) {
        Point a = Q[i] - p, b = Q[(i + 1) % Q.size()] - p;
        if (a.imag() > b.imag()) swap(a, b);
        if (a.imag() <= 0 && 0 < b.imag() && cross(a, b) < 0) in = !in;
        if (cross(a, b) == 0 && dot(a, b) <= 0) return ON;
    }
    return in ? IN : OUT;
}

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/4/CGL_4_C
// 凸多角形の切断
// 直線 l.a-l.b で切断しその左側にできる凸多角形を返す
Polygon convex_cut(const Polygon &U, Line l) {
    Polygon ret;
    for (int i = 0; i < U.size(); i++) {
        Point now = U[i], nxt = U[(i + 1) % U.size()];
        if (ccw(l.a, l.b, now) != -1) ret.push_back(now);
        if (ccw(l.a, l.b, now) * ccw(l.a, l.b, nxt) < 0) {
            ret.push_back(crosspoint(Line(now, nxt), l));
        }
    }
    return (ret);
}

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/3/CGL_3_A
// 多角形の面積
Real area(const Polygon &p) {
    Real A = 0;
    for (int i = 0; i < p.size(); ++i) {
        A += cross(p[i], p[(i + 1) % p.size()]);
    }
    return A * 0.5;
}

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/7/CGL_7_H
// 多角形と円の共通部分の面積
Real area(const Polygon &p, const Circle &c) {
    if (p.size() < 3) return 0.0;
    auto cross_area = [&](auto&& cross_area, const Circle &c, const Point &a, const Point &b) -> Real{
        Point va = c.p - a, vb = c.p - b;
        Real f = cross(va, vb), ret = 0.0;
        if (equals(f, 0.0)) return ret;
        if (max(abs(va), abs(vb)) < c.r + EPS) return f;
        if (distance(Segment(a, b), c.p) > c.r - EPS) return c.r * c.r * arg(vb * conj(va));
        auto u = crosspoint(c, Segment(a, b));
        vector<Point> tot{a, u.first, u.second, b};
        for (int i = 0; i + 1 < tot.size(); i++) {
            ret += cross_area(cross_area, c, tot[i], tot[i + 1]);
        }
        return ret;
    };
    Real A = 0;
    for (int i = 0; i < p.size(); i++) {
        A += cross_area(cross_area, c, p[i], p[(i + 1) % p.size()]);
    }
    return A * 0.5;
}

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/4/CGL_4_B
// 凸多角形の直径(最遠頂点対間距離)
Real convex_diameter(const Polygon &p) {
    int N = (int)p.size();
    int is = 0, js = 0;
    for (int i = 1; i < N; i++) {
        if (p[i].imag() > p[is].imag()) is = i;
        if (p[i].imag() < p[js].imag()) js = i;
    }
    Real maxdis = abs(p[is] - p[js]);

    int maxi, maxj, i, j;
    i = maxi = is;
    j = maxj = js;
    do {
        if (cross(p[(i + 1) % N] - p[i], p[(j + 1) % N] - p[j]) >= 0) {
            j = (j + 1) % N;
        } else {
            i = (i + 1) % N;
        }
        if (abs(p[i] - p[j]) > maxdis) {
            maxdis = abs(p[i] - p[j]);
            maxi = i;
            maxj = j;
        }
    } while (i != is || j != js);
    return maxdis;
}

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/5/CGL_5_A
// 最近点対
Real closest_pair(Points ps) {
    if (ps.size() <= 1) throw(0);
    sort(begin(ps), end(ps), compare_x);

    const Real INF = 1e18;

    auto rec = [&](auto&&rec, int left, int right) -> Real{
        if (right - left <= 1) return INF;
        int mid = (left + right) >> 1;
        auto x = real(ps[mid]);
        auto ret = min(rec(rec, left, mid), rec(rec, mid, right));
        inplace_merge(begin(ps) + left, begin(ps) + mid, begin(ps) + right, compare_y);

        vector<Point> nears;
        for (int i = left; i < right; i++) {
            if (abs(real(ps[i]) - x) >= ret) continue;

            int sz = nears.size();
            for (int j = sz - 1; j >= 0; j--) {
                auto p = ps[i] - nears[j];
                if (imag(p) >= ret) break;
                ret = min(ret, abs(p));
            }
            nears.emplace_back(ps[i]);
        }
        return ret;
    };
    return rec(rec, 0, (int)ps.size());
}

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/7/CGL_7_B
// 三角形の内接円
Circle incircle(Point p1, Point p2, Point p3) {
    Point p23 = p1 + (p2 - p1) * polar((Real)1.0, arg((p3 - p1) / (p2 - p1)) / (Real)2.0);
    Point p13 = p2 + (p3 - p2) * polar((Real)1.0, arg((p1 - p2) / (p3 - p2)) / (Real)2.0);

    Line l1(p1, p23), l2(p2, p13);
    Point p = crosspoint(l1, l2);
    Real r = distance(Line(p1, p2), p);
    return Circle(p, r);
}

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/7/CGL_7_C
// 三角形の外接円
Circle circumcircle(Point p1, Point p2, Point p3) {
    Point p23 = (p2 + p3) / (Real)2.0;
    Point p13 = (p1 + p3) / (Real)2.0;

    Line l1 = Line(p23, p23 + rotate(p3 - p2, PI / 2));
    Line l2 = Line(p13, p13 + rotate(p3 - p1, PI / 2));
    Point p = crosspoint(l1, l2);
    Real r = distance(p1, p);
    return Circle(p, r);
}

// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/7/CGL_7_I
// 2円の共通部分の面積
Real intersection_area(Circle c1, Circle c2) {
    Real rd = abs(c1.p - c2.p);
    if(rd <= c1.r - c2.r + EPS) {
        return c2.r * c2.r * PI;
    }
    if(rd + EPS >= c1.r + c2.r) {
        return (Real)0.0;
    }

    Real t1 = acos((c1.r * c1.r + rd * rd - c2.r * c2.r) / (2 * c1.r * rd));
    Real t2 = acos((c2.r * c2.r + rd * rd - c1.r * c1.r) / (2 * c2.r * rd));

    Real ret = c1.r * c1.r * t1 + c2.r * c2.r * t2;
    ret -= c1.r * rd * sin(t1);
    return ret;
}


int main() {
    ll N;
    cin >> N;
    vc<Circle> cs(N);

    Point ct(0, 0);

    vc<tuple<Point, int, bool>> ps;
    rep(i, N) {
        cin >> cs[i].p >> cs[i].r;
        auto [p1, p2] = tangent(cs[i], ct);
        if(ccw(Point(0, 0), p1, p2) == -1) {
            swap(p1, p2);
        }
        ps.eb(p1, i, true);
        ps.eb(p2, i, false);
    }

    sort(all(ps), [&](auto a, auto b) {
        auto[p1, id1, b1] = a;
        auto[p2, id2, b2] = b;
        auto arg1 = arg(p1);
        auto arg2 = arg(p2);

        if (equals(-PI, arg1)) arg1 = PI;
        if (equals(-PI, arg2)) arg2 = PI;

        if(!equals(arg1, arg2)){
            return arg1 < arg2;
        }else if(b1 != b2){
            return b1 < b2;
        }else{
            return distance(ct, cs[id1].p) < distance(ct, cs[id2].p);
        }
    });

    vc<ld> dists(N);
    rep(i, N) {
        dists[i] = distance(ct, cs[i].p);
    }

    ps.insert(ps.end(), ps.begin(), ps.end());

    auto comp = [&](ll a, ll b) {
        return dists[a] < dists[b];
    };

    ll now = -1;
    set<ll> ans;
    set<ll, decltype(comp)> st{comp};
    for (auto [p, id, b] : ps) {
        if (b) {
            st.emplace(id);

            if(now != -1 and *st.begin() != now) {
                now = -1;
            }

            if(now == -1 and *st.begin() == id) {
                now = id;
            }
        } else {
            if(st.find(id) != st.end()) {
                st.erase(id);
            }

            if (now == -1) continue;

            if(distance(ct, cs[id].p) < distance(ct, cs[now].p)) {
                now = -1;
            }

            if (now == id) {
                ans.emplace(id);
                now = -1;
            }
        }
    }

    repa(a, ans) {
        cout << a + 1 << " ";
    }
    cout << endl;
}