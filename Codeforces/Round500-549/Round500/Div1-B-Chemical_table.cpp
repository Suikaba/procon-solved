#include <bits/stdc++.h>
using namespace std;

using ll = long long;

class union_find {
public:
    union_find(int n) : par(n, -1) {}

    int root(int x) {
        return par[x] < 0 ? x : par[x] = root(par[x]);
    }

    bool unite(int x, int y) {
        x = root(x), y = root(y);
        if(x == y) return false;
        if(par[x] > par[y]) swap(x, y);
        par[x] += par[y];
        par[y] = x;
        return true;
    }

private:
    vector<int> par;
};

int main() {
    int n, m, q; cin >> n >> m >> q;
    vector<int> r(q), c(q);
    map<int, int> xi, yi;
    vector<int> xs, ys;
    union_find uf(q);
    for(int i = 0; i < q; ++i) {
        cin >> r[i] >> c[i];
        xs.push_back(c[i]), ys.push_back(r[i]);
        if(yi.count(r[i]) == 0) {
            yi[r[i]] = i;
        } else {
            uf.unite(i, yi[r[i]]);
        }
        if(xi.count(c[i]) == 0) {
            xi[c[i]] = i;
        } else {
            uf.unite(i, xi[c[i]]);
        }
    }
    sort(begin(xs), end(xs)); xs.erase(unique(begin(xs), end(xs)), end(xs));
    sort(begin(ys), end(ys)); ys.erase(unique(begin(ys), end(ys)), end(ys));
    set<int> cmps;
    for(int i = 0; i < q; ++i) {
        cmps.insert(uf.root(i));
    }

    cout << cmps.size() - 1 + (n - ys.size()) + (m - xs.size()) << endl;
}
