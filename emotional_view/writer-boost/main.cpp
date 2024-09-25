#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
using namespace std;
namespace mp = boost::multiprecision;
using Bint = mp::cpp_int;
using Real = mp::cpp_dec_float_100;
using T = tuple<Bint, Bint, Bint>;
using ll = long long;

#define VARIABLE(x) cerr << "# " << #x << " = " << (x) << endl;

template<typename Monoid, typename OperatorMonoid = Monoid>
struct LazySegmentTree{
    private:
    using F = function<Monoid(Monoid, Monoid)>;
    using G = function<Monoid(Monoid, OperatorMonoid)>;
    using H = function<OperatorMonoid(OperatorMonoid, OperatorMonoid)>;

    int size_, offset_, zeroindex_;
    vector<Monoid> data_;
    vector<OperatorMonoid> lazy_;
    const F f;
    const G g;
    const H h;
    const Monoid m1_;
    const OperatorMonoid om1_;

    inline void check_(int x){
        assert(1 <= x && x <= size_);
    }

    void eval_(int k){
        if(lazy_[k] == om1_) return;
        if(k < size_){
            lazy_[k * 2 + 0] = h(lazy_[k * 2 + 0], lazy_[k]);
            lazy_[k * 2 + 1] = h(lazy_[k * 2 + 1], lazy_[k]);
        }
        data_[k] = g(data_[k], lazy_[k]);
        lazy_[k] = om1_;
    }

    void update_(int ul, int ur, OperatorMonoid x, int left, int right, int cell){
        eval_(cell);
        if(ul <= left && right <= ur){
            lazy_[cell] = h(lazy_[cell], x);
            eval_(cell);
        }
        else if(ul < right && left < ur){
            int mid = (left + right) / 2;
            update_(ul, ur, x, left, mid, cell * 2 + 0);
            update_(ul, ur, x, mid, right, cell * 2 + 1);
            data_[cell] = f(data_[cell * 2 + 0], data_[cell * 2 + 1]);
        }
    }

    Monoid query_(int ql, int qr, int left, int right, int cell){
        eval_(cell);
        if(qr <= left || right <= ql){
            return m1_;
        }
        if(ql <= left && right <= qr){
            return data_[cell];
        }
        int mid = (left + right) / 2;
        Monoid ans_left = query_(ql, qr, left, mid, cell * 2 + 0);
        Monoid ans_right = query_(ql, qr, mid, right, cell * 2 + 1);
        return f(ans_left, ans_right);
    }

    public:
    /**
     * @brief セグメント木を要素数 `Size` で初期化する。
     * @param Size セグメント木の要素数
     * @param Merge 区間取得を行う演算
     * @param Mapping 遅延評価の適用を行う演算
     * @param Composite 遅延評価の合成を行う演算
     * @param Monoid_Identity モノイドの単位元
     * @param OperatorMonoid_Identity 操作モノイドの単位元
     * @param ZeroIndex 0-indexとして扱いたいか (default = `false`)
     */
    LazySegmentTree(int Size, F Merge, G Mapping, H Composite,
    const Monoid &Monoid_Identity, const OperatorMonoid &OperatorMonoid_Identity, bool ZeroIndex = false)
    : f(Merge), g(Mapping), h(Composite), m1_(Monoid_Identity), om1_(OperatorMonoid_Identity), zeroindex_(ZeroIndex){
        size_ = 1;
        while(size_ < Size) size_ <<= 1;
        offset_ = size_ - 1;
        data_.resize(2 * size_, m1_);
        lazy_.resize(2 * size_, om1_);
    }

    /**
     * @brief セグメント木を構築する。
     * @attention 必ず `set()` で初期値を代入してから呼び出すこと！
     */
    void build(){
        for(int i = offset_; i >= 1; --i){
            data_[i] = f(data_[i * 2 + 0], data_[i * 2 + 1]);
        }
    }

    /**
     * @brief セグメント木の初期値を代入する。
     * @param Index 代入先の要素番号 (default = 1-index)
     * @param Value 代入する値
     */
    void set(int Index, Monoid Value){
        check_(Index + zeroindex_);
        data_[offset_ + Index + zeroindex_] = Value;
    }

    /**
     * @brief セグメント木を配列 `Init_Data` で初期化する。
     * @param Init_Data 初期データの配列
     * @param Merge 区間取得を行う演算
     * @param Mapping 遅延評価の適用を行う演算
     * @param Composite 遅延評価の合成を行う演算
     * @param Monoid_Identity モノイドの単位元
     * @param OperatorMonoid_Identity 操作モノイドの単位元
     * @param ZeroIndex 0-indexとして扱いたいか (default = `false`)
     */
    LazySegmentTree(vector<Monoid> &Init_Data, F Merge, G Mapping, H Composite,
    const Monoid &Monoid_Identity, const OperatorMonoid &OperatorMonoid_Identity, bool ZeroIndex = false)
    : f(Merge), g(Mapping), h(Composite), m1_(Monoid_Identity), om1_(OperatorMonoid_Identity), zeroindex_(ZeroIndex){
        size_ = 1;
        while(size_ < (int)Init_Data.size()) size_ <<= 1;
        offset_ = size_ - 1;
        data_.resize(2 * size_, m1_);
        lazy_.resize(2 * size_, om1_);
        for(int i = 0; i < (int)Init_Data.size(); ++i){
            data_[size_ + i] = Init_Data[i];
        }
        build();
    }

    /**
     * @brief 半開区間 `[left, Right)` に対して区間更新クエリを処理する。
     * @param Left 半開区間の左端
     * @param Right 半開区間の右端
     * @param OP 更新操作
     */
    void update(int Left, int Right, OperatorMonoid OP){
        check_(Left + zeroindex_);
        check_(Right + zeroindex_ - 1);
        update_(Left + zeroindex_, Right + zeroindex_, OP, 1, size_ + 1, 1);
    }

    /**
     * @brief 半開区間 `[Left, Right)` に対して区間取得クエリを行う。
     * @param Left 半開区間の左端
     * @param Right 半開区間の右端
     * @return Monoid 取得した結果
     */
    Monoid query(int Left, int Right){
        check_(Left + zeroindex_);
        check_(Right + zeroindex_ - 1);
        return query_(Left + zeroindex_, Right + zeroindex_, 1, size_ + 1, 1);
    }

    /**
     * @brief 要素番号 `k` の要素を取得する。
     * @param k 取得先の要素番号 (default = 1-index)
     * @return Monoid 取得した結果
     */
    Monoid get(int k){
        check_(k + zeroindex_);
        return query(k, k + 1);
    }

    Monoid operator[](const int &k){
        return get(k);
    }

    void print(){
        int cnt = 1, i = 1, depth = 1;
        while(1){
            if(i >= size_ * 2) break;
            cerr << depth++ << " : ";
            for(int c = 0; c < cnt; ++c){
                cerr << data_[i++] << " ";
            }
            cerr << endl;
            cnt <<= 1;
        }
    }
};

Real offset = mp::pow(Real(10), 90);

struct Spot{
    Real x, y, r, d;
    Spot(Real x_ = 0.0, Real y_ = 0.0, Real r_ = 0.0) : x(x_), y(y_), r(r_){
        d = mp::sqrt(x * x + y * y - r * r);
    }
    T arg(){
        Bint arg1 = static_cast<Bint>(mp::floor(mp::atan2(d * y + r * x, d * x - r * y) * offset));
        Bint arg2 = static_cast<Bint>(mp::floor(mp::atan2(d * y - r * x, d * x + r * y) * offset));
        Bint arg3 = static_cast<Bint>(mp::floor(mp::atan2(y, x) * offset));
        return {min(arg1, arg2), arg3, max(arg1, arg2)};
    }
};

int main(){
    int N; cin >> N;
    vector<Spot> emo_spot;
    vector<pair<ll, int>> d_square;
    vector<Bint> argments;
    for(int i = 0; i < N; ++i){
        ll x, y, r; cin >> x >> y >> r;
        emo_spot.push_back(Spot(x, y, r));
        d_square.push_back({x * x + y * y - r * r, i});
        auto [a1, a2, a3] = emo_spot.back().arg();
        argments.push_back(a1);
        argments.push_back(a2);
        argments.push_back(a3);
    }
    sort(d_square.begin(), d_square.end());
    argments.push_back(static_cast<Bint>(mp::floor(mp::acos(Real(-1)) * offset)));
    argments.push_back(static_cast<Bint>(mp::floor(mp::acos(Real(-1)) * -1 * offset)));
    sort(argments.begin(), argments.end());
    argments.erase(unique(argments.begin(), argments.end()), argments.end());
    auto find = [&](Bint value) -> int {
        return lower_bound(argments.begin(), argments.end(), value) - argments.begin();
    };

    // for(Real ar : argments){
    //     cerr << "# " << static_cast<Bint>(ar) << endl;
    // }

    LazySegmentTree<int> seg(argments.size(), [&](int f, int g){return max(f, g);}, [&](int f, int g){return g;}, [&](int f, int g){return g == 0 ? f : g;}, 0, 0, true);
    seg.build();
    vector<int> ans;
    for(auto [_, i] : d_square){
        auto [left_arg, __, right_arg] = emo_spot[i].arg();
        int l = find(left_arg), r = find(right_arg);
        if(left_arg < 0 and right_arg > 0 and emo_spot[i].x < 0){
            if(!(seg.query(r, argments.size()) || seg.query(0, l + 1))){
                ans.push_back(i + 1);
            }
            seg.update(r + 1, argments.size(), 1);
            seg.update(0, l, i + 1);
        }
        else{
            if(!seg.query(l, r + 1)) ans.push_back(i + 1);
            seg.update(l + 1, r, i + 1);
        }
    }
    sort(ans.begin(), ans.end());
    for(int i = 0; i < ans.size(); ++i){
        cout << ans[i] << " \n"[i + 1 == ans.size()];
        // cerr << (int)x[ans[i] - 1] << " " << (int)y[ans[i] - 1] << " " << (int)r[ans[i] - 1] << " : " << ans[i] << endl;
    }
}