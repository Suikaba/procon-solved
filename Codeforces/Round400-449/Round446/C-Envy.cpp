#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

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

    int& operator[](size_t i) { return par[i]; }

private:
    vector<int> par;
};

struct edge {
    edge(int u_, int v_, int w_) : u(u_), v(v_), w(w_) {}
    bool operator<(edge const& that) const {
        return w < that.w;
    }
    int u, v, w;
};

struct query {
    query(int u_, int v_, int w_, int i) : u(u_), v(v_), w(w_), idx(i) {}
    bool operator<(query const& that) const {
        if(w != that.w) return w < that.w;
        return idx < that.idx;
    }
    int u, v, w, idx;
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int n, m; cin >> n >> m;
    vector<edge> es; es.reserve(m);
    for(int i = 0; i < m; ++i) {
        int u, v, w; cin >> u >> v >> w;
        es.emplace_back(u - 1, v - 1, w);
    }
    int q; cin >> q;
    vector<query> qs; qs.reserve(500000);
    for(int i = 0; i < q; ++i) {
        int k; cin >> k;
        for(int j = 0; j < k; ++j) {
            int eid; cin >> eid;
            qs.emplace_back(es[eid - 1].u, es[eid - 1].v, es[eid - 1].w, i);
        }
    }
    sort(begin(es), end(es));
    sort(begin(qs), end(qs));

    union_find uf(n), uf2(n);
    vector<bool> ans(q, true);
    int qi = 0;
    for(int i = 0; i < m; ++i) {
        while(qi < (int)qs.size() && qs[qi].w == es[i].w) {
            int r = qi;
            while(r < (int)qs.size() && qs[qi].idx == qs[r].idx && qs[qi].w == qs[r].w) {
                if(!uf2.unite(uf.root(qs[r].u), uf.root(qs[r].v))) {
                    ans[qs[qi].idx] = false;
                }
                ++r;
            }
            for(int j = qi; j < r; ++j) {
                uf2[uf.root(qs[j].u)] = uf2[uf.root(qs[j].v)] = -1;
            }
            qi = r;
        }

        int j = i;
        while(j < (int)es.size() && es[i].w == es[j].w) {
            uf.unite(es[j].u, es[j].v);
            ++j;
        }
        i = j - 1;
    }

    for(int i = 0; i < q; ++i) {
        cout << (ans[i] ? "YES" : "NO") << "\n";
    }
}
