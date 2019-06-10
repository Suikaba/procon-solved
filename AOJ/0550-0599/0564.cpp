#include <bits/stdc++.h>
using namespace std;

// BIT なしで解ける気と思うけど、まあいいや（は？）

using ll = long long;
using pii = pair<int, int>;

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

int main() {
    int n; cin >> n;
    vector<tuple<int, int, int>> v(n);
    vector<pii> as(n);
    for(int i = 0; i < n; ++i) {
        int a, b; cin >> a >> b;
        v[i] = make_tuple(b, a, i);
        as[i] = make_pair(a, i);
    }
    sort(begin(v), end(v), greater<>{});
    sort(begin(as), end(as));
    vector<int> idx(n);
    for(int i = 0; i < n; ++i) {
        idx[as[i].second] = i;
    }

    ll ans = 0, lower_sum = 0;
    fenwick_tree<ll> bit(n), cnt(n);
    priority_queue<pii> lower; // (val, idx)
    for(int i = 0; i < n; ++i) {
        int a, b, id; tie(b, a, id) = v[i];
        id = idx[id];
        if(a <= b) {
            lower.emplace(a, id);
            lower_sum += a;
        } else {
            bit.add(id, a);
            cnt.add(id, 1);
        }
        while(!lower.empty() && lower.top().first > b) {
            const int val = lower.top().first;
            const int j = lower.top().second;
            lower.pop();
            lower_sum -= val;
            bit.add(j, val);
            cnt.add(j, 1);
        }
        auto check = [&] (int p) {
            const ll k = lower.size() + cnt.sum(0, p);
            return k * b >= lower_sum + bit.sum(0, p);
        };
        int lb = 0, ub = n + 1;
        while(ub - lb > 1) {
            const int mid = (ub + lb) >> 1;
            (check(mid) ? lb : ub) = mid;
        }
        ans = max(ans, (ll)lower.size() + cnt.sum(0, lb));
    }

    cout << ans << endl;
}
