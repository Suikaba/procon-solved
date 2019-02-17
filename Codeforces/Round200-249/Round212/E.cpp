#include <bits/stdc++.h>
using namespace std;

// tag: 最小費用流
// 解法
// i -> j に容量 c[i][j] でコスト0の辺をはり、i -> j に容量 inf でコスト1の辺を張るだけ。
// このグラフで「実際に x 流せる」かつ「x 流したときのコストが k 以下」である最大の x が答え。
// これは二分探索じゃなくて最初にノーコストという制約で流してから、1つずつ流量増やすのが計算量的には正しい。
// けどなんか二分探索で余裕で通ってしまうのはだめだろ。
// あと二分探索した場合、関数内部でオーバーフローしうるので long long にする必要があった。
// やっぱり1ずつ流すべきですね。

template <typename Edge>
class graph {
    using graph_t = std::vector<std::vector<Edge>>;
public:
    using reference = std::vector<Edge>&;
    using const_reference = std::vector<Edge> const&;
    using iterator = typename graph_t::iterator;
    using const_iterator = typename graph_t::const_iterator;
    using reverse_iterator = typename graph_t::reverse_iterator;

    graph() : g() {}
    graph(int n) : g(n) {}

    reference operator[](int x) { return g[x]; }
    const_reference operator[](int x) const { return g[x]; }

    iterator begin() { return std::begin(g); }
    const_iterator begin() const { return std::begin(g); }
    iterator end() { return std::end(g); }
    const_iterator end() const { return std::end(g); }
    reverse_iterator rbegin() { return std::rbegin(g); }
    reverse_iterator rend() { return std::rend(g); }

    int size() const { return g.size(); }
    int edge_size(int i) const { return g[i].size(); }

    void add_node(std::vector<Edge> es) {
        g.push_back(std::move(es));
    }

    void add_edge(int node_idx, Edge e) {
        g[node_idx].push_back(std::move(e));
    }

private:
    std::vector<std::vector<Edge>> g;
};

template <typename Capacity>
class capacity_edge {
public:
    using capacity_type = Capacity;
    int to, rev;
    capacity_type cap;
    capacity_edge(int t, int r, capacity_type c) : to(t), rev(r), cap(c) {}
};

template <typename Capacity, typename Cost>
class capacity_weighted_edge {
public:
    using capacity_type = Capacity;
    using cost_type = Cost;
    int to, rev;
    capacity_type cap;
    cost_type cost;
    capacity_weighted_edge(int t, int r, capacity_type cp, cost_type c)
        : to(t), rev(r), cap(cp), cost(c)
    {}
};

template <typename Capacity, typename Cost>
class capacity_weighted_graph : public graph<capacity_weighted_edge<Capacity, Cost>> {
    using base_type = graph<capacity_weighted_edge<Capacity, Cost>>;
public:
    capacity_weighted_graph(int n) : base_type(n) {}

    using base_type::add_edge;
    using base_type::edge_size;
    void add_edge(int from, int to, Capacity cap, Cost cost) {
        add_edge(from, capacity_weighted_edge<Capacity, Cost>{to, edge_size(to), cap, cost});
        add_edge(to, capacity_weighted_edge<Capacity, Cost>{from, edge_size(from) - 1, Capacity{0}, -cost});
    }
};


template <typename Edge>
typename Edge::cost_type min_cost_flow(graph<Edge>& g, int s, int t, typename Edge::capacity_type f) {
    using cost_type = typename Edge::cost_type;
    using P = std::pair<cost_type, int>;
    const auto inf = std::numeric_limits<cost_type>::max() / 2;
    cost_type res = 0;
    std::vector<cost_type> h(g.size()), dist(g.size());
    std::vector<int> prevv(g.size()), preve(g.size());
    while(f > 0) {
        std::priority_queue<P, std::vector<P>, std::greater<>> que;
        std::fill(std::begin(dist), std::end(dist), inf);
        dist[s] = 0;
        que.emplace(dist[s], s);
        while(!que.empty()) {
            const auto cur_d = que.top().first;
            const int v = que.top().second;
            que.pop();
            if(dist[v] < cur_d) continue;
            for(int i = 0; i < (int)g[v].size(); ++i) {
                auto& e = g[v][i];
                if(e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
                    dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
                    prevv[e.to] = v;
                    preve[e.to] = i;
                    que.emplace(dist[e.to], e.to);
                }
            }
        }
        if(dist[t] == inf) return -1;
        for(int v = 0; v < (int)g.size(); ++v) {
            h[v] += dist[v];
        }

        auto d = f;
        for(int v = t; v != s; v = prevv[v]) {
            d = std::min(d, g[prevv[v]][preve[v]].cap);
        }
        f -= d;
        res += d * h[t];
        for(int v = t; v != s; v = prevv[v]) {
            auto& e = g[prevv[v]][preve[v]];
            e.cap -= d;
            g[v][e.rev].cap += d;
        }
    }
    return res;
}

using ll = long long;
constexpr int inf = 1e9;

int main() {
    int n, k; cin >> n >> k;
    capacity_weighted_graph<ll, ll> g(n);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            int c; cin >> c;
            if(c > 0) {
                g.add_edge(i, j, c, 0);
                g.add_edge(i, j, inf, 1);
            }
        }
    }

    ll lb = 0, ub = inf;
    while(ub - lb > 1) {
        const auto mid = (ub + lb) >> 1;
        auto gg = g;
        const auto f = min_cost_flow(gg, 0, n - 1, mid);
        (f != -1 && f <= k ? lb : ub) = mid;
    }

    cout << lb << endl;
}
