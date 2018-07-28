
// http://codeforces.com/contest/540/problem/E

// 反省点
// 結構バグった．実装ミスと言うかは解法がおぼろげなイメージのまま書いたせい．
// 自分には書きながら解法詰めるのは無理なんだから，100％詰めきったと思えるまで書かないぐらいがちょうどいいかもしれない．

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

class fenwick_tree {
public:
    fenwick_tree(int n_) : n(n_), dat(n, 0) {}
    void add(int i, int value) {
        for(; i < n; i |= i + 1) {
            dat[i] += value;
        }
    }
    int sum(int i) const {
        int res = 0;
        for(; i >= 0; i = (i & (i + 1)) - 1) {
            res += dat[i];
        }
        return res;
    }
    int sum(int l, int r) const {
        return sum(r - 1) - sum(l - 1);
    }

private:
    int n;
    vector<int> dat;
};

int main() {
    int n;
    cin >> n;
    vector<int> a(n), b(n), xs;
    for(int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i];
        xs.push_back(a[i]), xs.push_back(b[i]);
    }
    sort(begin(xs), end(xs));
    xs.erase(unique(begin(xs), end(xs)), end(xs));
    for(int i = 0; i < n; ++i) {
        a[i] = lower_bound(begin(xs), end(xs), a[i]) - begin(xs);
        b[i] = lower_bound(begin(xs), end(xs), b[i]) - begin(xs);
    }

    const int m = xs.size();
    vector<int> v(m);
    iota(begin(v), end(v), 0);
    for(int i = 0; i < n; ++i) {
        swap(v[a[i]], v[b[i]]);
    }

    ll ans = 0;
    fenwick_tree bit(m);
    for(int i = 0; i < m; ++i) {
        ans += bit.sum(v[i], m);
        bit.add(v[i], 1);
    }
    for(int i = 0; i < m; ++i) {
        ans += abs(xs[i] - xs[v[i]]) - abs(i - v[i]);
    }
    cout << ans << endl;
}
