#include <bits/stdc++.h>
using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2390

// 反省点
// 厳密な証明が甘い気がする．だってそうじゃなきゃAOJ-ICPC 700点もないでしょこの問題．
// 考察と実装合わせて10分ぐらい．

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
private:
    vector<int> par;
};

struct edge {
    int u, v, cost;
    bool operator<(edge const& e) const {
        return cost < e.cost;
    }
};

int main() {
    int n, t, k;
    int cs = 1;
    while(cin >> n >> t >> k, n) {
        vector<edge> es(n - 1);
        int ans = 0;
        for(int i = 0; i < n - 1; ++i) {
            cin >> es[i].u >> es[i].v >> es[i].cost;
            es[i].u--; es[i].v--;
            ans += es[i].cost;
        }
        vector<bool> is_base(n);
        for(int i = 0; i < t; ++i) {
            int b; cin >> b;
            is_base[b - 1] = true;
        }
        sort(rbegin(es), rend(es));
        union_find uf(n);
        int can = t - k - 1;
        for(auto& e : es) {
            int u = uf.root(e.u), v = uf.root(e.v);
            if(is_base[u] && is_base[v]) {
                if(can > 0) {
                    can--;
                    ans -= e.cost;
                    uf.unite(u, v);
                }
            } else {
                uf.unite(u, v);
                ans -= e.cost;
                bool b1 = is_base[u], b2 = is_base[v];
                is_base[u] = is_base[u] | b2;
                is_base[v] = is_base[v] | b1;
            }
        }

        cout << "Case " << cs++ << ": " << ans << endl;
    }
}
