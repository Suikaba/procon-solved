// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2374

// 解法
// O(n(logn)^2) 解法は区間add一点取得ができるデータ構造でやるだけ。
// 使うときは余ってる中で一番大きい方から優先的に使うやつ。

// O(n) 解法があるらしいが、わかってないのでまた今度

// O(n(logn)^2)
#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
 
template <typename T>
class fenwick_tree {
public:
    fenwick_tree(int n_) : n(n_), dat(n, 0) {}
 
    void add(int i, T value) {
        for(; i < n; i |= i + 1) {
            dat[i] += value;
        }
    }
 
    T sum(int i) const {
        T res = 0;
        for(; i >= 0; i = (i & (i + 1)) - 1) {
            res += dat[i];
        }
        return res;
    }
    // [l, r)
    T sum(int l, int r) const {
        return sum(r - 1) - sum(l - 1);
    }
 
private:
    const int n;
    std::vector<T> dat;
};
 
template <typename T>
class range_add_range_sum {
public:
    range_add_range_sum(int n_) : n(n_), bit0(n), bit1(n) {}
 
    void add(int l, int r, T val) {
        bit0.add(l, -val * l);
        bit1.add(l, val);
        bit0.add(r, val * r);
        bit1.add(r, -val);
    }
 
    T sum(int p) const {
        return bit1.sum(p) * (p + 1) + bit0.sum(p);
    }
    T sum(int l, int r) const {
        return sum(r - 1) - sum(l - 1);
    }
 
private:
    const int n;
    fenwick_tree<T> bit0, bit1;
};
 
int main() {
    int m, n, m0, md, n0, nd;
    cin >> m >> n >> m0 >> md >> n0 >> nd;
    vector<int> ms(m), ns(n);
    ms[0] = m0, ns[0] = n0;
    for(int i = 1; i < m; ++i) {
        ms[i] = (ms[i - 1] * 58 + md) % (n + 1);
    }
    for(int i = 1; i < n; ++i) {
        ns[i] = (ns[i - 1] * 58 + nd) % (m + 1);
    }
    sort(rbegin(ms), rend(ms));
    sort(begin(ns), end(ns));
 
    range_add_range_sum<ll> rars(n);
    for(int i = 0; i < n; ++i) {
        rars.add(i, i + 1, ns[i]);
    }
    auto get_pos = [&] (int val) {
        int lb = -1, ub = n;
        while(ub - lb > 1) {
            const int mid = (lb + ub) >> 1;
            (rars.sum(mid, mid + 1) >= val ? ub : lb) = mid;
        }
        return ub;
    };
    ll ans = 0;
    for(int i = 0; i < m; ++i) {
        if(ms[i] == 0) break;
        const int v = rars.sum(n - ms[i], n - ms[i] + 1);
        const int p1 = get_pos(v), p2 = get_pos(v + 1);
        if(p2 != n) {
            ans += n - p2;
            rars.add(p2, n, -1);
        }
        if(v != 0) {
            ans += ms[i] - (n - p2);
            rars.add(p1, p1 + ms[i] - (n - p2), -1);
        }
    }
 
    cout << ans << endl;
}