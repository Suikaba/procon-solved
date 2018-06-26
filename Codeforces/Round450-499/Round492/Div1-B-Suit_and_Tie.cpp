#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// 0-indexed
template <typename T>
class fenwick_tree {
public:
    fenwick_tree(int n) : n(n), dat(n, 0) {}

    void add(int i, T value) {
        for(; i<n; i |= i + 1) {
            dat[i] += value;
        }
    }

    T sum(int i) const {
        T res = 0;
        for(; i>=0; i = (i & (i+1)) - 1) {
            res += dat[i];
        }
        return res;
    }
    // [l, r)
    T sum(int l, int r) const {
        return sum(r-1) - sum(l-1);
    }

private:
    const int n;
    std::vector<T> dat;
};

int main() {
    int n;
    cin >> n;
    n *= 2;
    vector<int> a(n);
    fenwick_tree<int> bit(n);
    map<int, vector<int>> pos;
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
        pos[a[i]].push_back(i);
    }
    vector<bool> ok(n);
    ll ans = 0;
    for(int i = 0; i < n; ++i) {
        if(ok[i]) continue;
        //cout << "i: " << i << endl;
        int npos = pos[a[i]][1];
        ans += npos - i - 1 + bit.sum(i, npos);
        //cout << npos << ' ' << i << ' ' << bit.sum(i, npos) << endl;
        bit.add(npos, -1);
        ok[i] = ok[npos] = true;
    }

    cout << ans << endl;
}
