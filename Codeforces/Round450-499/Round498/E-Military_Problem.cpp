#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q; cin >> n >> q;
    vector<vector<int>> g(n);
    for(int i = 1; i < n; ++i) {
        int p; cin >> p;
        g[p - 1].push_back(i);
    }
    vector<int> l(n), r(n), vs(n);
    int iter = 0;
    function<void(int)> euler_tour = [&] (int v) {
        l[v] = iter;
        vs[iter++] = v;
        sort(begin(g[v]), end(g[v]));
        for(auto to : g[v]) {
            euler_tour(to);
        }
        r[v] = iter;
    };
    euler_tour(0);

    while(q--) {
        int u, k; cin >> u >> k;
        u--, k--;
        if(l[u] + k >= r[u]) {
            cout << -1 << endl;
        } else {
            cout << vs[l[u] + k] + 1 << endl;
        }
    }
}
