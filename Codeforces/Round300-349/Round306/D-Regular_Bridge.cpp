#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
    int k;
    cin >> k;
    if(k % 2 == 0) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        if(k == 1) {
            cout << 2 << ' ' << 1 << endl;
            cout << 1 << ' ' << 2 << endl;
            return 0;
        }
        const int n = k + 2;
        priority_queue<pii> que;
        vector<vector<int>> g(n);
        for(int i = 0; i < k - 1; ++i) {
            g[0].push_back(i + 1);
        }
        for(int i = 1; i < n; ++i) {
            que.emplace(i < k ? k - 1 : k, i);
        }
        while(!que.empty()) {
            auto v = que.top();
            que.pop();
            vector<pii> nxt;
            for(int i = 0; i < v.first; ++i) {
                auto v2 = que.top();
                que.pop();
                g[v.second].push_back(v2.second);
                nxt.emplace_back(v2.first - 1, v2.second);
            }
            for(auto& p : nxt) {
                que.push(move(p));
            }
        }
        cout << 2 * n << ' ' << n * k << endl;
        cout << 1 << ' ' << n + 1 << endl;
        for(int i = 0; i < n; ++i) {
            for(auto to : g[i]) {
                cout << i + 1 << ' ' << to + 1 << endl;
                cout << i + n + 1 << ' ' << to + 1 + n << endl;
            }
        }
    }
}
