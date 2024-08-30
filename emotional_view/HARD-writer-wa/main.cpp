#include <bits/stdc++.h>
using namespace std;

#define VARIABLE(x) cerr << "# " << #x << " = " << (x) << endl;

/**
 * @file LazySegmentTree.hpp
 * @author log K (lX57)
 * @brief Lazy Segment Tree - 遅延評価セグメント木
 * @version 2.0
 * @date 2023-10-02
 */

#include <bits/stdc++.h>
using namespace std;

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

using ll = long long;
using ld = long double;

const ll offset = 1000000000LL;

int main(){
    int N; cin >> N;
    vector<ld> x(N), y(N), r(N);
    for(int i = 0; i < N; ++i) cin >> x[i] >> y[i] >> r[i];

    vector<pair<ld, int>> d_square(N);
    vector<ld> d(N), L_square(N);
    for(int i = 0; i < N; ++i){
        d_square[i] = {x[i] * x[i] + y[i] * y[i] - r[i] * r[i], i};
        d[i] = sqrt(x[i] * x[i] + y[i] * y[i] - r[i] * r[i]);
        L_square[i] = x[i] * x[i] + y[i] * y[i];
    }
    using P = pair<ld, ld>;
    vector<pair<ll, ll>> argment_list(N);
    vector<ll> argments;
    for(int i = 0; i < N; ++i){
        ld coef = d[i] / L_square[i];
        P p1, p2;
        p1 = {coef * (d[i] * x[i] - r[i] * y[i]), coef * (d[i] * y[i] + r[i] * x[i])};
        p2 = {coef * (d[i] * x[i] + r[i] * y[i]), coef * (d[i] * y[i] - r[i] * x[i])};
        ld arg1 = atan2l(p1.second, p1.first), arg2 = atan2l(p2.second, p2.first), arg3 = atan2l(y[i], x[i]);
        ll arg_conv_1 = arg1 * offset, arg_conv_2 = arg2 * offset, arg_conv_3 = arg3 * offset;
        argment_list[i] = {min(arg_conv_1, arg_conv_2), max(arg_conv_1, arg_conv_2)};
        argments.push_back(arg_conv_1), argments.push_back(arg_conv_2), argments.push_back(arg_conv_3);
    }
    sort(d_square.begin(), d_square.end());
    argments.push_back(acosl(-1) * offset);
    argments.push_back(acosl(-1) * offset * -1);
    sort(argments.begin(), argments.end());
    argments.erase(unique(argments.begin(), argments.end()), argments.end());
    auto find = [&](ll value) -> int {
        return lower_bound(argments.begin(), argments.end(), value) - argments.begin();
    };
    // for(auto ar : argments){
    //     cout << ar << endl;
    // }
    LazySegmentTree<int> seg(argments.size(), [&](int f, int g){return f || g;}, [&](int f, int g){return f || g;}, [&](int f, int g){return f || g;}, 0, 0, true);
    seg.build();
    vector<int> ans;
    for(auto [_, i] : d_square){
        auto [left_value, right_value] = argment_list[i];
        int left = find(left_value), right = find(right_value);
        // VARIABLE(i + 1);
        // VARIABLE(x[i]);
        // VARIABLE(y[i]);
        // VARIABLE(r[i]);
        // VARIABLE(left);
        // VARIABLE(right);
        if(left_value < 0 and right_value > 0 and x[i] < 0){
            // VARIABLE(seg.query(right, argments.size()) || seg.query(0, left + 1));
            if(!(seg.query(right, argments.size()) || seg.query(0, left + 1))){
                ans.push_back(i + 1);
            }
            seg.update(right + 1, argments.size(), 1);
            seg.update(0, left, 1);
        }
        else{
            // VARIABLE(seg.query(left, right + 1));
            if(!seg.query(left, right + 1)) ans.push_back(i + 1);
            seg.update(left + 1, right, 1);
        }
    }
    sort(ans.begin(), ans.end());
    for(int i = 0; i < ans.size(); ++i){
        cout << ans[i] << " \n"[i + 1 == ans.size()];
    }
}