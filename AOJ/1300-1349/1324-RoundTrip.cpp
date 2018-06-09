#include <bits/stdc++.h>
using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1324

// 反省
// 考察に手間取った．実装は楽．
// 逆グラフも作って行きと戻りを同時に動かしていけば街の状態が持てることに気づくのに時間がかかった．
// これぐらいはすぐ思いつきたかったね．

constexpr int inf = 1e9;

struct edge {
    int to, cost;
};

using edges = vector<edge>;
using graph = vector<edges>;

int main() {
    int n, m;
    while(cin >> n >> m, n) {
        vector<int> height(n), fee(n), bit(n);
        height[n - 1] = 1000;
        vector<int> h_cnt(1000);
        for(int i = 1; i < n - 1; ++i) {
            cin >> fee[i] >> height[i];
            bit[i] = h_cnt[height[i]]++;
        }
        graph g(n), rg(n);
        for(int i = 0; i < m; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            g[a - 1].push_back(edge{b - 1, c});
            rg[b - 1].push_back(edge{a - 1, c});
        }

        vector<vector<vector<int>>> d(n, vector<vector<int>>(n, vector<int>(1 << 10, inf)));
        d[0][0][1] = 0;
        using state = tuple<int, int, int, int>;
        priority_queue<state, vector<state>, greater<state>> que;
        que.emplace(0, 0, 0, 1);
        while(!que.empty()) {
            int cur_d, u, v, S;
            tie(cur_d, u, v, S) = que.top();
            que.pop();
            const int cur_h = max(height[u], height[v]);
            for(auto& e : g[u]) {
                if(height[e.to] < cur_h) continue;
                const int nS = (1 << bit[e.to]) | (height[e.to] > cur_h ? 0 : S);
                const int nxt_d = cur_d + (height[e.to] == cur_h && (S & (1 << bit[e.to])) ? 0 : fee[e.to]) + e.cost;
                if(nxt_d < d[e.to][v][nS]) {
                    d[e.to][v][nS] = nxt_d;
                    que.emplace(nxt_d, e.to, v, nS);
                }
            }
            for(auto& e : rg[v]) {
                if(height[e.to] < cur_h) continue;
                const int nS = (1 << bit[e.to]) | (height[e.to] > cur_h ? 0 : S);
                const int nxt_d = cur_d + (height[e.to] == cur_h && (S & (1 << bit[e.to])) ? 0 : fee[e.to]) + e.cost;
                if(d[u][e.to][nS] > nxt_d) {
                    d[u][e.to][nS] = nxt_d;
                    que.emplace(nxt_d, u, e.to, nS);
                }
            }
        }

        cout << (d[n - 1][n - 1][1] == inf ? -1 : d[n - 1][n - 1][1]) << endl;
    }
}
