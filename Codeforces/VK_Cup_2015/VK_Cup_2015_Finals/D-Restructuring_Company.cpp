// http://codeforces.com/contest/566/problem/D

#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

constexpr int inf = 1e9;

class union_find {
public:
    union_find(int n) : par(n, -1) {}

    int root(int x) { return par[x] < 0 ? x : par[x] = root(par[x]); }

    void unite(int x, int y) {
        x = root(x), y = root(y);
        if(x == y) return;
        if(par[x] > par[y]) swap(x, y);
        par[x] += par[y];
        par[y] = x;
    }

    bool same(int x, int y) {
        return root(x) == root(y);
    }

private:
    vector<int> par;
};

struct team {
public:
    team(int r) : rep(r), rng(r, r) {}
    team(int r, pii rng_) : rep(r), rng(rng_) {}
    bool operator<(team const& other) const {
        return rng < other.rng;
    }
    int rep;
    pii rng;
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, q; cin >> n >> q;
    set<team> s;
    for(int i = 0; i < n; ++i) {
        s.emplace(i);
    }
    union_find uf(n);
    for(int i = 0; i < q; ++i) {
        int qtype, x, y; cin >> qtype >> x >> y;
        x--, y--;
        if(qtype == 1) {
            uf.unite(x, y);
        } else if(qtype == 2) {
            const auto lb = prev(s.upper_bound(team(x, make_pair(x, inf)))), ub = s.upper_bound(team(y, make_pair(y, inf)));
            int l = lb->rng.first, r = l;
            for(auto it = lb; it != ub; ++it) {
                uf.unite(lb->rep, it->rep);
                r = max(r, it->rng.second);
            }
            s.erase(lb, ub);
            s.emplace(uf.root(l), make_pair(l, r));
        } else {
            cout << (uf.same(x, y) ? "YES" : "NO") << endl;
        }
    }
}
