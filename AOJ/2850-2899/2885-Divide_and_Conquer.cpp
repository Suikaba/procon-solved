// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2885

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    while(cin >> n >> m, n) {
        vector<vector<int>> g(n);
        for(int i = 0; i < m; ++i) {
            int a, b; cin >> a >> b;
            g[a - 1].push_back(b - 1);
            g[b - 1].push_back(a - 1);
        }
        vector<int> col(n, -1), cnt(2);
        function<void(int, int)> coloring =
            [&] (int v, int c) {
                if(col[v] != -1 && col[v] != c) throw runtime_error("");
                if(col[v] != -1) return;
                col[v] = c;
                cnt[c] += 1;
                for(auto to : g[v]) {
                    coloring(to, !c);
                }
            };
        try {
            coloring(0, 0);
        } catch (...) {
            cout << 0 << endl;
            continue;
        }
        set<int> s;
        if(cnt[0] % 2 == 0) s.insert(cnt[0] / 2);
        if(cnt[1] % 2 == 0) s.insert(cnt[1] / 2);
        cout << s.size() << endl;
        for(auto x : s) {
            cout << x << endl;
        }
    }
}
