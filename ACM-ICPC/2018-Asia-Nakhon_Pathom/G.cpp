#include <bits/stdc++.h>
using namespace std;


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

struct directed_edge {
    directed_edge(int t) : to(t) {}
    int to;
};

using directed_graph = graph<directed_edge>;

void add_edge(directed_graph& g, int from, int to) {
    g[from].emplace_back(to);
}

template <typename Edge>
std::vector<int> scc(graph<Edge> const& g) {
    const int n = g.size();
    int idx = 0, k = 0, s = 0;
    std::vector<int> ord(n, -1), low(n), on_s(n), cmp(n), stk(n);
    std::function<void(int)> dfs = [&] (int v) {
        ord[v] = low[v] = idx++;
        stk[s++] = v;
        on_s[v] = true;
        for(const auto& e : g[v]) {
            if(ord[e.to] == -1) {
                dfs(e.to);
                low[v] = std::min(low[v], low[e.to]);
            } else if(on_s[e.to]) {
                low[v] = std::min(low[v], ord[e.to]);
            }
        }
        if(low[v] == ord[v]) {
            while(true) {
                const int w = stk[--s];
                on_s[w] = false;
                cmp[w] = k;
                if(w == v) break;
            }
            ++k;
        }
    };
    for(int v = 0; v < n; ++v) {
        if(ord[v] == -1) dfs(v);
    }

    return cmp;
}

int main() {
    int T; cin >> T;
    while(T--) {
        int n; cin >> n;
        directed_graph g(n);
        int e; cin >> e;
        for(int i = 0; i < e; ++i) {
            int a, b; cin >> a >> b;
            add_edge(g, a, b);
        }
        auto cmp = scc(g);
        set<int> s(cmp.begin(), cmp.end());
        cout << s.size() << endl;
    }
}
