
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2785

// 解法
// とりあえず C[i] については無視して考えてみる。
// 最終日に使うドリンクを決めたとする。このドリンクを k とする。
// すると、L - a[k] をできるだけ早く達成したいということになり、
// 当然 a[i] - b[i] が大きい方から貪欲に飲むのが最適である。
// 以降 a[i] - b[i] の降順でソートされているとする。
//
// L - a[i] を達成する最小日数を求めるが、これは以下の2通りがある。
// - 場合1：ドリンク k より前のドリンクを飲んだ時点で達成
// - 場合2：ドリンク k 以降のドリンクを飲んだ時点で達成
//
// 場合1は簡単で、a[i] - b[i] の累積和（の max）が L - a[i] 以上となる位置を
// 二分探索で求めれば良い。
//
// 場合2のときは、0 ～ k - 1 までの a[i] - b[i] の総和を S として、
// (a[i + 1] - b[i + 1]) + ... + (a[j] - b[j]) が L - a[i] - S 以上となる最小の j を探索する。
// このために、区間 [l, r) に対し、[l, i) (l < i <= r) なる全ての i について考えたときの (a[l] - b[l]) + ... + (a[i - 1] - b[i - 1]) の最大値を求める必要があり、これは segment tree で実現できる。
//
// こうして得られた最小日数の id を x としよう。
// 最後に c[i] について考える。これは a[i] - b[i] - c[i] の累積和について、先と同じように2通りに分けられる。
//
// 場合1は簡単であり、a[i] - b[i] - c[i] の x までの累積和（の min）が 0 より大きければ OK である。
//
// 場合2のときは、a[i] - b[i] - c[i] の k まで (exclusive k) の累積和が 0 より大きい、かつ (k + 1 から x までの "a[i] - b[i] - c[i - 1] の" 累積和の min) + (0 から k までの累積和）が 0 より大きければ OK である。
// k を使えないので、インデックスが1つずれていることに注意する。
// これも segment tree（max のときと同じ要領）で処理することができる。
//
// あとはすべての k についてこれをやれば良い。
// segment tree の上で二分探索をしたので O(n (logn)^2) で解ける。
// ちゃんとやれば log はもう一つ落とせるが、まあ間に合うのでよし。

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

constexpr ll inf = 1e18;

template<typename Monoid>
class segment_tree {
    using T = typename Monoid::type;

public:
    segment_tree(std::vector<T> const& init)
        : sz(init.size()), n(expand(init.size()))
    {
        dat.assign(n*2, Monoid::id());
        std::copy(begin(init), end(init), begin(dat) + n);
        for(int i = n - 1; i >= 0; --i) {
            dat[i] = Monoid::op(dat[i * 2], dat[i * 2 + 1]);
        }
    }

    segment_tree(int const n_, T const& init = Monoid::id())
        : segment_tree(std::vector<T>(n_, init))
    {}

    void update(int p, T val) {
        assert(0 <= p && p < sz);
        dat[p += n] = val;
        while(p /= 2) {
            dat[p] = Monoid::op(dat[p * 2], dat[p * 2 + 1]);
        }
    }

    // [l, r)
    T query(int l, int r) const {
        assert(0 <= l && l <= r && r <= sz);
        l += n, r += n;
        T res1 = Monoid::id(), res2 = Monoid::id();
        while(l != r) {
            if(l & 1) res1 = Monoid::op(res1, dat[l++]);
            if(r & 1) res2 = Monoid::op(dat[--r], res2);
            l /= 2, r /= 2;
        }
        return Monoid::op(res1, res2);
    }

private:
    int expand(int n_) const {
        assert(n_ >= 1);
        return n_ == 1 ? n_ : expand((n_ + 1) / 2) * 2;
    }

private:
    const int sz, n;
    std::vector<T> dat;
};

struct RSMQ {
    struct type {
        ll sum, mini, maxi;
        type() : sum(0), mini(inf), maxi(-inf) {}
        type(ll s, ll mi, ll ma) : sum(s), mini(mi), maxi(ma) {}
    };
    static type id() {
        return type{0, inf, -inf};
    }
    static type op(type const& l, type const& r) {
        if(l.mini == inf) return r;
        if(r.mini == inf) return l;
        return type(l.sum + r.sum,
                    min(l.mini, l.sum + r.mini),
                    max(l.maxi, l.sum + r.maxi));
    }
};

int main() {
    ll n, l; cin >> n >> l;
    vector<pll> drink(n);
    vector<ll> c(n);
    for(int i = 0; i < n; ++i) {
        cin >> drink[i].first >> drink[i].second;
    }
    for(int i = 0; i < n; ++i) {
        cin >> c[i];
    }
    sort(begin(drink), end(drink), [] (const pll& p1, const pll& p2) {
        return p1.first - p1.second > p2.first - p2.second;
    });

    // a[i] - b[i], a[i] - b[i] - c[i], a[i] - b[i] - c[i - 1]
    vector<RSMQ::type> dat1(n), dat2(n), dat3(n);
    for(int i = 0; i < n; ++i) {
        const ll a = drink[i].first, b = drink[i].second;
        dat1[i] = RSMQ::type{a - b, a - b, a - b};
        dat2[i] = RSMQ::type{a - b - c[i], a - b - c[i], a - b - c[i]};
        if(i != 0) {
            dat3[i] = RSMQ::type{a - b - c[i - 1], a - b - c[i - 1], a - b - c[i - 1]};
        }
    }
    segment_tree<RSMQ> seg1(dat1), seg2(dat2), seg3(dat3);

    int ans = n + 1;
    for(int i = 0; i < n; ++i) { // last use
        const ll r = l - drink[i].first;
        if(r <= 0) {
            ans = 1;
            break;
        }
        if(seg1.query(0, i).maxi < r) {
            if(seg2.query(0, i).mini <= 0) continue;
            int lb = i + 1, ub = n;
            const ll s = seg1.query(0, i).sum;
            while(ub - lb > 1) {
                const int mid = (ub + lb) >> 1;
                (seg1.query(i + 1, mid).maxi < r - s ? lb : ub) = mid;
            }
            if(seg1.query(i + 1, ub).maxi < r - s) continue;
            if(seg2.query(0, i).sum + seg3.query(i + 1, ub).mini <= 0) continue;
            ans = min(ans, ub);
        } else {
            int lb = 0, ub = i;
            while(ub - lb > 1) {
                const int mid = (lb + ub) >> 1;
                (seg1.query(0, mid).maxi < r ? lb : ub) = mid;
            }
            if(seg2.query(0, ub).mini <= 0) continue;
            ans = min(ans, ub + 1);
        }
    }

    cout << (ans == n + 1 ? -1 : ans) << endl;
}