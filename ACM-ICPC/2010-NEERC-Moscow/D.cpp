#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
constexpr int inf = 1e9;

struct edge {
    int to, cost;
    edge(int t, int c) : to(t), cost(c) {}
};

using edges = vector<edge>;
using graph = vector<edges>;

void add_edge(graph& g, int from, int to, int cost) {
    g[from].emplace_back(to, cost);
    g[to].emplace_back(from, cost);
}

int main() {
    int n, k, l; cin >> n >> k >> l;
    vector<int> s(n);
    for(int i = 0; i < n; ++i) {
        cin >> s[i];
        s[i]--;
    }
    graph g(k);
    for(int i = 0; i < l; ++i) {
        int a, b, d; cin >> a >> b >> d;
        add_edge(g, a - 1, b - 1, d);
    }

    sort(begin(s), end(s));
    s.erase(unique(begin(s), end(s)), end(s));
    if((int)s.size() != n) {
        cout << 0 << endl;
        return 0;
    }

    vector<int> dist(k, inf), memo(k, -1);
    vector<int> d2(k, inf);
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> que;
    for(int i = 0; i < n; ++i) {
        dist[s[i]] = 0;
        memo[s[i]] = i;
        que.emplace(0, s[i], i);
    }
    while(!que.empty()) {
        const auto [cur_d, v, p] = que.top();
        que.pop();
        if(cur_d > dist[v]) continue;
        for(auto const& e : g[v]) {
            if(memo[e.to] != -1 && memo[e.to] != p) {
                d2[e.to] = min(d2[e.to], cur_d + dist[e.to] + e.cost);
            }
            if(dist[e.to] > cur_d + e.cost) {
                memo[e.to] = p;
                dist[e.to] = cur_d + e.cost;
                que.emplace(dist[e.to], e.to, p);
            }
        }
    }

    cout << *min_element(begin(d2), end(d2)) * 3 << endl;
}
