#include <bits/stdc++.h>
using namespace std;

// 解法 - 01BFS, O(n + m)
// ゴールからの dp.
// dp[u] := u からスタートしてゴールに至るまでに必要な命令数
// 遷移は dp[u] = min(min(dp[v]) + 1, max(dp[v])) (forall v | u -> v)
// min(dp[v]) + 1 は簡単で、u についたら命令して v に行くように仕向けるということを意味する。
// max(dp[v]) は、命令をしないということ。つまり、いける場所すべての max が最低限必要になる。

constexpr int inf = 1e9;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<vector<int>> rg(n);
    vector<int> out_deg(n);
    for(int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        rg[b - 1].push_back(a - 1);
        out_deg[a - 1] += 1;
    }
    int s, t; cin >> s >> t;
    s--, t--;

    vector<int> dp(n, inf);
    vector<bool> vis(n);
    dp[t] = 0;
    deque<int> que;
    que.push_back(t);
    while(!que.empty()) {
        const int u = que.front(); que.pop_front();
        if(vis[u]) continue; // これがないと WA。out_deg を余計に減らしてしまうから。
        vis[u] = true;
        for(auto const v : rg[u]) { // from
            out_deg[v]--;
            // max の遷移に対応する。
            // out_deg[v] が 0 になるのは、すべての行先について dp の値が確定したとき。
            // また 01BFS をしているから、そのときの dp[u] の値が max に対応している。
            if(out_deg[v] == 0) {
                if(dp[v] > dp[u]) {
                    dp[v] = dp[u];
                    que.push_front(v);
                }
            } else {
                // min の遷移に対応。説明は max と同じなので略。
                if(dp[v] > dp[u] + 1) {
                    dp[v] = dp[u] + 1;
                    que.push_back(v);
                }
            }
        }
    }

    cout << (dp[s] == inf ? -1 : dp[s]) << endl;
}
