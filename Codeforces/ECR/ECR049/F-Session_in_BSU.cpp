#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

class union_find {
public:
    union_find(int n) : par(n, -1) {}

    void init() {
        fill(begin(par), end(par), -1);
    }

    int root(int x) {
        return par[x] < 0 ? x : par[x] = root(par[x]);
    }

    bool unite(int x, int y) {
        x = root(x), y = root(y);
        if(x == y) return false;
        if(par[x] < par[y]) swap(x, y);
        par[x] += par[y];
        par[y] = x;
        return true;
    }

    int size(int x) {
        return -par[root(x)];
    }

private:
    vector<int> par;
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<pii> vs;
    vector<int> xs;
    for(int i = 0; i < n; ++i) {
        int a, b; cin >> a >> b;
        vs.emplace_back(a, i);
        vs.emplace_back(b, i);
        xs.push_back(a);
        xs.push_back(b);
    }
    sort(begin(xs), end(xs));
    sort(begin(vs), end(vs));
    xs.erase(unique(begin(xs), end(xs)), end(xs));
    for(auto& p : vs) {
        p.first = lower_bound(begin(xs), end(xs), p.first) - begin(xs);
    }

    union_find uf(n);
    vector<int> id(xs.size(), -1), cnt(n), maxi(n, -1);
    auto check = [&] (int x) {
        uf.init();
        fill(begin(id), end(id), -1);
        fill(begin(cnt), end(cnt), 0);
        fill(begin(maxi), end(maxi), -1);
        for(auto const& p : vs) {
            if(p.first <= x) {
                if(id[p.first] == -1) id[p.first] = p.second;
                else                  uf.unite(id[p.first], p.second);
            }
        }
        for(auto const& p : vs) {
            if(p.first > x) continue;
            int vi = uf.root(p.second);
            if(maxi[vi] < p.first) {
                maxi[vi] = p.first;
                cnt[vi] += 1;
            }
        }
        for(int i = 0; i < n; ++i) {
            if(cnt[uf.root(i)] < uf.size(i)) return false;
        }
        return true;
    };
    int lb = -1, ub = xs.size();
    while(ub - lb > 1) {
        const auto mid = (lb + ub) >> 1;
        (check(mid) ? ub : lb) = mid;
    }
    if(ub == (int)xs.size()) {
        cout << -1 << endl;
    } else {
        cout << xs[ub] << endl;
    }
}
