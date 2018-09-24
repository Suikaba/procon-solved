#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

struct edge {
    int to, cost;
};

using graph = vector<vector<edge>>;

void add_edge(graph& g, int from, int to, int w) {
    g[from].push_back(edge{to, w});
}

int read_number(string const& s, int& p) {
    int res = 0;
    while(p < (int)s.size() && isdigit(s[p])) {
        res = res * 10 + (s[p++] - '0');
    }
    return res;
}

int main() {
    int n, c; cin >> n >> c;
    vector<int> a(c), b(c), d(c), arbs;
    vector<char> o(c), s(c);
    for(int i = 0; i < c; ++i) {
        string cons; cin >> cons;
        int p = 0;
        a[i] = read_number(cons, p) - 1;
        if(cons[p] == '*') arbs.push_back(i);
        o[i] = cons[p];
        p += (cons[p] == '*' ? 1 : 2); // '*' or '<='
        b[i] = read_number(cons, p) - 1;
        s[i] = cons[p++];
        d[i] = read_number(cons, p);
    }

    int ans = -1;
    const int m = (int)arbs.size();
    for(int S = 0; S < (1 << m); ++S) {
        for(int i = 0; i < m; ++i) {
            o[arbs[i]] = (S & (1 << i)) ? '<' : '>';
        }
        graph g(n);
        for(int i = 0; i < c; ++i) {
            if(o[i] == '<') {
                if(s[i] == '+') {
                    add_edge(g, b[i], a[i], -d[i]);
                } else {
                    add_edge(g, a[i], b[i], d[i]);
                    add_edge(g, b[i], a[i], 0);
                }
            } else if(o[i] == '>') {
                if(s[i] == '+') {
                    add_edge(g, a[i], b[i], -d[i]);
                } else {
                    add_edge(g, b[i], a[i], d[i]);
                    add_edge(g, a[i], b[i], 0);
                }
            }
        }
        for(int i = 1; i < n; ++i) add_edge(g, i, 0, 0); // 0 is first

        int last_update = -1;
        vector<int> dist(n, inf);
        dist[0] = 0;
        for(int lp = 0; lp < n; ++lp) {
            for(int v = 0; v < n; ++v) {
                for(auto& e : g[v]) {
                    if(dist[e.to] > dist[v] + e.cost) {
                        last_update = lp;
                        dist[e.to] = dist[v] + e.cost;
                    }
                }
            }
        }
        if(last_update != n - 1) {
            ans = max(ans, *max_element(begin(dist), end(dist)));
        }
    }

    if(ans == inf) cout << "inf" << endl;
    else           cout << ans << endl;
}
