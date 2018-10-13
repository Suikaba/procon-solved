#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while(t--) {
        int n, k, f; cin >> n >> k >> f;
        vector<vector<int>> g(n);
        vector<int> deg(n);
        for(int i = 0; i < f; ++i) {
            int a, b; cin >> a >> b;
            deg[a - 1] += 1;
            deg[b - 1] += 1;
            g[a - 1].push_back(b - 1);
            g[b - 1].push_back(a - 1);
        }

        queue<int> que;
        for(int i = 0; i < n; ++i) {
            if(deg[i] < k) {
                deg[i] = -1;
                que.push(i);
            }
        }

        int ans = n;
        while(!que.empty()) {
            auto v = que.front(); que.pop();
            ans--;
            for(auto to : g[v]) {
                if(deg[to] == -1) continue;
                deg[to]--;
                if(deg[to] < k) {
                    que.push(to);
                    deg[to] = -1;
                }
            }
        }

        cout << ans << endl;
    }
}
