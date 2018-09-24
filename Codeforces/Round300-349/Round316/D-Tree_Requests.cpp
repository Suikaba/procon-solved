#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n);
    for(int i = 1; i < n; ++i) {
        int p; cin >> p;
        g[p - 1].push_back(i);
    }
    string s; cin >> s;
    vector<int> bit(26);
    for(int i = 0; i < 26; ++i) {
        bit[i] = 1 << i;
    }

    vector<vector<pii>> hs(1 << 20, vector<pii>(1, make_pair(0, 0)));
    vector<int> l(n), r(n);
    {
        int cur = 1;
        function<void(int, int)> euler_tour = [&] (int v, int d) {
            l[v] = cur;
            hs[d].emplace_back(cur, hs[d].back().second ^ bit[s[v] - 'a']);
            for(auto to : g[v]) {
                euler_tour(to, d + 1);
            }
            r[v] = ++cur;
        };
        euler_tour(0, 1);
    }

    for(int i = 0; i < m; ++i) {
        int v, h; cin >> v >> h;
        v--;
        const auto lb = lower_bound(begin(hs[h]), end(hs[h]), make_pair(l[v], -1)) - begin(hs[h]) - 1;
        const auto ub = lower_bound(begin(hs[h]), end(hs[h]), make_pair(r[v], -1)) - begin(hs[h]) - 1;
        const auto t = hs[h][ub].second ^ hs[h][lb].second;
        cout << ((t - (t & -t)) == 0 ? "Yes" : "No") << endl;
    }
}
