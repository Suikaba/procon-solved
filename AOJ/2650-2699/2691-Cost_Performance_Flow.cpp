#include <bits/stdc++.h>
using namespace std;

using ll = __int128;

ll abs(ll a) {
    return a < 0 ? -a : a;
}

template <typename NumType>
class rational {
public:
    rational(NumType n) : num(n), den(1) {}
    rational(NumType n, NumType d) : num(n), den(d) {}

    rational& operator+=(NumType n) {
        num += n * den;
        reduce();
        return *this;
    }
    rational& operator+=(rational const& r) {
        num = num * r.den + r.num * den;
        den = den * r.den;
        reduce();
        return *this;
    }
    rational& operator-=(NumType n) {
        num -= n * den;
        reduce();
        return *this;
    }
    rational& operator-=(rational const& r) {
        num = num * r.den - r.num * den;
        den = den * r.den;
        reduce();
        return *this;
    }
    rational& operator*=(NumType n) {
        num *= n;
        reduce();
        return *this;
    }
    rational& operator*=(rational const& r) {
        num *= r.num;
        den *= r.den;
        reduce();
        return *this;
    }

    void reduce() {
        const ll g = __gcd(abs(num), abs(den));
        num /= g, den /= g;
    }

    NumType numerator() const { return num; }
    NumType denominator() const { return den; }

    bool operator<(rational<NumType> const& r) const {
        return num * r.den < r.num * den;
    }
    bool operator<=(rational<NumType> const& r) const {
        return num * r.den <= r.num * den;
    }

private:
    NumType num, den;
};

template <typename NumType>
rational<NumType> operator+(NumType n, rational<NumType> r) {
    r += n;
    return r;
}
template <typename NumType>
rational<NumType> operator+(rational<NumType> a, rational<NumType> const& b) {
    a += b;
    return a;
}
template <typename NumType>
rational<NumType> operator-(NumType n, rational<NumType> const& r) {
    return rational<NumType>{n, 1} - r;
}
template <typename NumType>
rational<NumType> operator-(rational<NumType> a, rational<NumType> const& b) {
    a -= b;
    return a;
}
template <typename NumType>
rational<NumType> operator*(NumType n, rational<NumType> r) {
    r *= n;
    return r;
}
template <typename NumType>
rational<NumType> operator*(rational<NumType> a, rational<NumType> const& b) {
    a *= b;
    return a;
}

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

    void add_node(std::vector<Edge> es) {
        g.push_back(std::move(es));
    }

private:
    std::vector<std::vector<Edge>> g;
};

template <typename Capacity, typename Cost>
struct capacity_weighted_edge {
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
using capacity_weighted_graph = graph<capacity_weighted_edge<Capacity, Cost>>;

template <typename Capacity, typename Cost>
void add_edge(capacity_weighted_graph<Capacity, Cost>& g, int from, int to, Capacity cap, Cost cost) {
    g[from].emplace_back(to, static_cast<int>(g[to].size()), cap, cost);
    g[to].emplace_back(from, static_cast<int>(g[from].size() - 1), Capacity{0}, -cost);
}

template <typename Edge, typename Capacity = typename Edge::capacity_type>
Capacity augment(graph<Edge>& g, std::vector<int> const& level, std::vector<int>& iter, int v, int t, Capacity f) {
    if(v == t) return f;
    for(int& i = iter[v]; i < (int)g[v].size(); ++i) {
        auto& e = g[v][i];
        if(e.cap > 0 && level[v] < level[e.to]) {
            const auto d = augment(g, level, iter, e.to, t, std::min(f, e.cap));
            if(d > 0) {
                e.cap -= d;
                g[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

template <typename Edge, typename Capacity = typename Edge::capacity_type>
Capacity max_flow(graph<Edge>& g, int s, int t) {
    const auto inf = std::numeric_limits<Capacity>::max() / 2;
    Capacity flow = 0;
    while(true) {
        std::vector<int> level(g.size(), -1);
        level[s] = 0;
        std::queue<int> que;
        que.push(s);
        while(!que.empty()) {
            const int v = que.front();
            que.pop();
            for(auto const& e : g[v]) {
                if(e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    que.push(e.to);
                }
            }
        }

        if(level[t] < 0) return flow;
        std::vector<int> iter(g.size());
        Capacity f{0};
        while((f = augment(g, level, iter, s, t, inf)) > 0) {
            flow += f;
        }
    }
}

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

int main() {
    int n, m; cin >> n >> m;
    capacity_weighted_graph<int, int> g(n);
    int s, t; cin >> s >> t;
    s--, t--;
    for(int i = 0; i < m; ++i) {
        int a, b, u, c; cin >> a >> b >> u >> c;
        add_edge(g, a - 1, b - 1, u, c);
    }

    const ll M = [&] { auto tmp = g; return max_flow(tmp, s, t); }();

    rational<ll> ans{M * M, 1};
    auto calc_cost = [&] (ll fi, ll ci, ll ci_sum, rational<ll> delta) {
        const auto a = M - (fi + delta), b = ci_sum + ci * delta;
        return a * a + b * b;
    };
    ll ci_sum = 0;
    for(int i = 0; i < M; ++i) {
        const ll ci = min_cost_flow(g, s, t, 1);
        if(0 <= M - i - ci * ci_sum && M - i - ci * ci_sum <= ci * ci + 1) {
            auto delta = rational<ll>{M - i - ci * ci_sum, ci * ci + 1};
            delta.reduce();
            ans = min(ans, calc_cost(i, ci, ci_sum, delta));
        }
        ci_sum += ci;
        ans = min(ans, calc_cost(i + 1, 0, ci_sum, rational<ll>{0, 1}));
    }

    cout << (long long)ans.numerator() << "/" << (long long)ans.denominator() << endl;
}

