#include <bits/stdc++.h>
using namespace std;

vector<int> tsort(vector<vector<int>> const& g) {
    const int n = g.size();
    vector<int> in(n);
    for(int i = 0; i < n; ++i) {
        for(auto to : g[i]) {
            ++in[to];
        }
    }
    vector<int> S;
    for(int i = 0; i < n; ++i) {
        if(in[i] == 0) {
            S.push_back(i);
        }
    }
    vector<int> res;
    while(!S.empty()) {
        int v = S.back();
        S.pop_back();
        res.push_back(v);
        for(auto to : g[v]) {
            --in[to];
            if(in[to] == 0) {
                S.push_back(to);
            }
        }
    }
    bool ok = true;
    for(int i = 0; i < n; ++i) {
        ok &= in[i] == 0;
    }
    if(!ok) {
        res.clear();
    }
    return res;
}


int main() {
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n);
    for(int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
    }
    auto ans = tsort(g);
    if(ans.empty()) {
        cout << 1 << endl;
    } else {
        cout << 0 << endl;
    }
}