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
        if(par[x] < par[y]) swap(x, y);
        par[x] += par[y];
        par[y] = x;
        return true;
    }

private:
    vector<int> par;
};

struct edge {
    int u, v;
    ll cost;
    edge(int x, int y, ll c) : u(x), v(y), cost(c) {}

    bool operator<(const edge& that) const {
        return cost < that.cost;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<vector<ll>> a(n, vector<ll>(m));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
    }

    vector<edge> es;
    for(int i = 0; i < n; ++i) {
        vector<pair<ll, int>> b;
        for(int j = 0; j < m; ++j) {
            b.emplace_back(a[i][j], i * m + j);
        }
        sort(begin(b), end(b));
        for(int j = 0; j < m - 1; ++j) {
            es.emplace_back(b[j].second, b[j + 1].second, b[j + 1].first - b[j].first);
        }
    }
    for(int i = 0; i < m; ++i) {
        vector<pair<ll, int>> b;
        for(int j = 0; j < n; ++j) {
            b.emplace_back(a[j][i], j * m + i);
        }
        sort(begin(b), end(b));
        for(int j = 0; j < n - 1; ++j) {
            es.emplace_back(b[j].second, b[j + 1].second, b[j + 1].first - b[j].first);
        }
    }
    sort(begin(es), end(es));
    union_find uf(n * m);
    ll ans = 0;
    for(auto const& e : es) {
        if(uf.unite(e.u, e.v)) {
            ans += e.cost;
        }
    }
    cout << ans << endl;
}
