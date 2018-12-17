#include <bits/stdc++.h>

using weight_t = int;
using capacity_t = int;

constexpr capacity_t inf = std::numeric_limits<capacity_t>::max() / 2;

struct edge {
    int to;
    weight_t w;
};

using edges = std::vector<edge>;
using graph = std::vector<edges>;

// Gomory-Hu Tree
// Solve: all-pairs maximum flow in "undirected" graph
// Complexity: O(V * maxFlow)
// Note: Now, I use Edmond Karp as max flow algorithm, so O(maxFlow) = O(VE^2)
class gomory_hu {
public:
    gomory_hu(int n) : built(false), cap(n, std::vector<capacity_t>(n)), gt(n) {}

    void add_edge(int s, int t, capacity_t c) {
        built = false;
        cap[s][t] = cap[t][s] = c;
    }

    void build() {
        const int n = cap.size();
        std::vector<int> p(n), prev;
        std::vector<capacity_t> w(n);
        for(int s = 1; s < n; ++s) {
            int t = p[s];
            std::vector<std::vector<int>> f(n, std::vector<int>(n));
            capacity_t total = 0;
            while(true) {
                std::queue<int> que;
                que.push(s);
                prev.assign(n, -1);
                prev[s] = -2;
                while(!que.empty() && prev[t] == -1) {
                    const int u = que.front(); que.pop();
                    for(int v = 0; v < n; ++v) {
                        if(prev[v] == -1 && cap[u][v] - (f[u][v] - f[v][u]) > 0) {
                            prev[v] = u;
                            que.push(v);
                        }
                    }
                }
                if(prev[t] == -1) break;
                capacity_t inc = inf;
                for(int v = t, u = prev[v]; u >= 0; v = u, u = prev[v]) {
                    inc = std::min(inc, cap[u][v] - (f[u][v] - f[v][u]));
                }
                for(int v = t, u = prev[v]; u >= 0; v = u, u = prev[v]) {
                    f[u][v] += inc;
                }
                total += inc;
            }
            w[s] = total;
            for(int i = 0; i < n; ++i) {
                if(i != s && prev[i] != -1 && p[i] == t) p[i] = s;
            }
            if(prev[p[t]] != -1) {
                p[s] = p[t];
                p[t] = s;
                w[s] = w[t];
                w[t] = total;
            }
        }
        for(int s = 0; s < n; ++s) {
            if(s == p[s]) continue;
            gt[s].push_back(edge{p[s], w[s]});
            gt[p[s]].push_back(edge{s, w[s]});
        }
        built = true;
    }

    std::vector<std::vector<weight_t>> all_pair_flow() const {
        assert(built);
        const int n = gt.size();
        std::vector<std::vector<weight_t>> res(n, std::vector<weight_t>(n, inf));
        for(int s = 0; s < n; ++s) {
            std::function<void(int, int, int)> dfs = [&] (int v, int p, weight_t w) {
                res[s][v] = w;
                for(auto const& e : gt[v]) {
                    if(e.to == p) continue;
                    dfs(e.to, v, std::min(w, e.w));
                }
            };
            dfs(s, -1, inf);
        }
        return res;
    }

    graph get_tree() const {
        return gt;
    }

private:
    bool built;
    std::vector<std::vector<capacity_t>> cap;
    graph gt; // gomory-hu tree
};


using namespace std;

int main() {
    int n, m; cin >> n >> m;
    gomory_hu gt(n);
    for(int i = 0; i < m; ++i) {
        int a, b, c; cin >> a >> b >> c;
        gt.add_edge(a - 1, b - 1, c);
    }
    gt.build();
    auto g = gt.get_tree();

    int cost = 0;
    vector<vector<bool>> used(n, vector<bool>(n));
    function<vector<int>(int)> build_path = [&] (int v) {
        int use_u = -1, use_v = -1, use_w = inf;
        function<void(int, int)> dfs = [&] (int u, int p) {
            for(auto const& e : g[u]) {
                if(e.to == p || used[u][e.to]) continue;
                if(e.w < use_w) {
                    use_u = u, use_v = e.to, use_w = e.w;
                }
                dfs(e.to, u);
            }
        };
        dfs(v, -1);

        if(use_u == -1) {
            vector<int> res = {v};
            return res;
        }
        used[use_u][use_v] = used[use_v][use_u] = true;
        cost += use_w;
        auto p1 = build_path(use_u), p2 = build_path(use_v);
        p1.insert(end(p1), begin(p2), end(p2));
        return p1;
    };
    const auto path = build_path(0);

    cout << cost << endl;
    for(int i = 0; i < n; ++i) {
        cout << path[i] + 1 << " \n"[i + 1 == n];
    }
}
