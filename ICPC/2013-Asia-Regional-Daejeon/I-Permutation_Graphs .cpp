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
    T sum(int l, int r) const {
        return sum(r - 1) - sum(l - 1);
    }

private:
    int n;
    vector<T> dat;
};

int main() {
    int T; cin >> T;
    while(T--) {
        int n; cin >> n;
        map<int, int> pos;
        vector<int> a(n);
        for(int i = 0; i < n; ++i) {
            int x; cin >> x;
            pos[x] = i;
        }
        for(int i = 0; i < n; ++i) {
            int x; cin >> x;
            a[i] = pos[x];
        }

        fenwick_tree<ll> bit(n);
        ll ans = 0;
        for(int i = 0; i < n; ++i) {
            ans += bit.sum(a[i] + 1, n);
            bit.add(a[i], 1);
        }
        cout << ans << endl;
    }
}
