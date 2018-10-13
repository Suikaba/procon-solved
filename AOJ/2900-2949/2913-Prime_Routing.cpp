// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2913

#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

using pii = pair<int, int>;

int main() {
    const int max_v = 1e6;
    vector<bool> is_prime(max_v, true);
    vector<int> ps;
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i < max_v; ++i) {
        if(is_prime[i]) {
            ps.push_back(i);
            for(int j = i + i; j < max_v; j += i) {
                is_prime[j] = false;
            }
        }
    }

    int n, m, s, t; cin >> n >> m >> s >> t;
    s--, t--;
    vector<vector<int>> g(n);
    for(int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        g[a - 1].push_back(b - 1);
        g[b - 1].push_back(a - 1);
    }

    vector<vector<int>> d(n, vector<int>(2, inf));
    d[s][0] = 0;
    queue<pii> que;
    que.emplace(s, 0);
    while(!que.empty()) {
        auto now = que.front(); que.pop();
        const int v = now.first, pari = now.second;
        for(auto to : g[v]) {
            if(d[to][!pari] > d[v][pari] + 1) {
                d[to][!pari] = d[v][pari] + 1;
                que.emplace(to, !pari);
            }
        }
    }
    if(d[t][0] == 2) {
        cout << 2 << endl;
    } else {
        if(d[t][1] == inf) {
            cout << -1 << endl;
        } else if(d[t][1] == 1) {
            cout << 3 << endl;
        } else {
            cout << *lower_bound(begin(ps), end(ps), d[t][1]) << endl;
        }
    }
}
