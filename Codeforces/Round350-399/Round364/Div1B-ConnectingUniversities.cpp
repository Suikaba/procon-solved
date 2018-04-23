#include <bits/stdc++.h>
using namespace std;

// http://codeforces.com/contest/700/problem/B

using ll = long long;
using pii = pair<int, int>;

int main() {
    int n, k;
    cin >> n >> k;
    set<int> univ;
    for(int i = 0; i < 2 * k; ++i) {
        int x; cin >> x;
        x--;
        univ.insert(x);
    }
    vector<vector<int>> g(n);
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a - 1].push_back(b - 1);
        g[b - 1].push_back(a - 1);
    }

    vector<ll> ans(n);
    function<int(int, int)> dfs = [&](int v, int par) {
        ans[v] += univ.count(v);
        for(auto to : g[v]) {
            if(to == par) continue;
            ans[v] += dfs(to, v);
        }
        return ans[v];
    };
    dfs(0, -1);
    function<void(int, int, int)> solve = [&](int v, int par, int down) {
        assert(ans[v] >= 0);
        vector<pii> ch;
        int sum = univ.count(v);
        for(auto to : g[v]) {
            if(to == par) continue;
            ch.emplace_back(ans[to], to);
            sum += ans[to];
        }
        if(ch.empty()) return;
        sort(begin(ch), end(ch));
        const int rest = sum - ch.back().first;
        if(ch.back().first > down + rest) {
            down += rest;
            ans[ch.back().second] = down;
            solve(ch.back().second, v, down);
        }
    };
    solve(0, -1, 0);

    cout << accumulate(begin(ans), end(ans), 0LL) - ans[0] << endl;
}
