// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2943

// 解法
// いつもの燃やす埋める（最小カット）。
// S側ならつけない、T 側ならつける、のイメージで辺にコストを決めるやつ（今回はちょっと違うが）。
// グラフの作り方は工夫が必要。
// 装置と照明を別に持つとカットにうまく意味をもたせられない。
// そこで装置だけを残して、4つの照明の利益を1つの辺にまとめてしまったグラフを考えてみる。
// S -> 照明 -> T は当然同じように意味をなさないが、これは
// ある照明が2つの異なる装置に影響されるからである。
// 装置の間にある影響は、隣接する行の装置同士でしか発生しない。
// この意味で装置は二部グラフであると言える。
// 偶数行目のある装置に注目する。
// その装置と照明をともにする4つの頂点から、その照明（1つ）の利益分の辺を注目した装置にはる。
// また、偶数行目の装置の頂点 v について、S -> v に W を、v -> T に4つの照明の総和の辺をはる。
// 奇数行目は逆に S -> v に4つの照明の総和を、v -> T に W をはる。
// S -> v、v -> T のカットの意味は最初に行ったのと同じだが、奇数行目と偶数行目で意味が逆になっている。
// 燃やす埋めるでは、0 or 1 を書く頂点に割りあてるイメージだが、
// 2つの装置を同時に利用したときに、重複して加算している照明の利益を引く必要がある。
// つまり、どちらの装置にも 1 が割り当てられたときのみ、重複利益を引きたい。
// 先のように意味を逆にしておくことで、装置間の辺の意味が「一方が 0 でもう一方が 1のとき」のコスト、
// つまり（片方の意味が逆転していることを考えれば）どちらも 1 のときのコスト、といえる。
// このグラフにおける最小カットを、装置が関係する4つの照明の和の総和から引いたものが答え。
// 二部グラフだということに気づくと言うよりは、重複を消すような辺を張るときに
// 偶然二部グラフであることが使えてラッキーという方が近いかも。

// 実装上の注意
// long long を使いましょう


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

// ============================================================================
// capacity graph (for maximum flow)
template <typename Capacity>
struct capacity_edge {
    using capacity_type = Capacity;
    int to, rev;
    capacity_type cap;
    capacity_edge(int t, int r, capacity_type c) : to(t), rev(r), cap(c) {}
};

template <typename Capacity>
using capacity_graph = graph<capacity_edge<Capacity>>;

template <typename Capacity>
void add_edge(capacity_graph<Capacity>& g, int from, int to, Capacity cap) {
    g[from].emplace_back(to, static_cast<int>(g[to].size()), cap);
    g[to].emplace_back(from, static_cast<int>(g[from].size() - 1), Capacity{0});
}


template <typename Edge, typename Capacity = typename Edge::capacity_type>
Capacity augment(graph<Edge>& g, std::vector<int> level, std::vector<int>& iter, int v, int t, Capacity f) {
    if(v == t) return f;
    for(int i = iter[v]; i < (int)g[v].size(); ++i) {
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

using ll = long long;

constexpr ll inf = 1e18;

int main() {
    int h, w, W; cin >> h >> w >> W;
    vector<vector<ll>> b(h, vector<ll>(w));
    for(int i = 0; i < h; ++i) {
        for(int j = 0; j < w; ++j) {
            cin >> b[i][j];
        }
    }

    const int source = (h - 1) * (w - 1);
    const int sink = source + 1;
    capacity_graph<ll> g((h - 1) * (w - 1) + 2);
    ll sum = 0;
    for(int i = 0; i < h - 1; ++i) {
        for(int j = 0; j < w - 1; ++j) {
            if((i + j) % 2 != 0) continue;
            const int v = i * (w - 1) + j;
            const ll c = b[i][j] + b[i + 1][j] + b[i][j + 1] + b[i + 1][j + 1];
            sum += c;
            if(i & 1) {
                add_edge(g, source, v, (ll)W);
                add_edge(g, v, sink, (ll)c);
                add_edge(g, (i - 1) * (w - 1) + j - 1, v, (ll)b[i][j]);
                add_edge(g, (i - 1) * (w - 1) + j + 1, v, (ll)b[i][j + 1]);
                if(i + 1 >= h - 1) continue;
                add_edge(g, (i + 1) * (w - 1) + j - 1, v, (ll)b[i + 1][j]);
                add_edge(g, (i + 1) * (w - 1) + j + 1, v, (ll)b[i + 1][j + 1]);
            } else {
                add_edge(g, source, v, (ll)c);
                add_edge(g, v, sink, (ll)W);
            }
            
        }
    }

    cout << sum - max_flow(g, source, sink) << endl;
}