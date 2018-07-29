
// http://codeforces.com/contest/544/problem/D

// 反省
// 共有するとしたら1つの部分パスだけ，というのに何故かすぐ気が付かなかった（同じの解いたことあるやろ）
// 気づいてからもパスを共有しないケースを書き忘れていた．
// めんどい方のケースで手間取った時，簡単な方のケースを忘れることが結構多いので気をつけましょう．

#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a - 1].push_back(b - 1);
        g[b - 1].push_back(a - 1);
    }
    int s1, t1, l1, s2, t2, l2;
    cin >> s1 >> t1 >> l1 >> s2 >> t2 >> l2;
    s1--; t1--; s2--; t2--;

    vector<vector<int>> dist(n, vector<int>(n, inf));
    for(int i = 0; i < n; ++i) {
        dist[i][i] = 0;
        queue<int> que;
        que.push(i);
        while(!que.empty()) {
            auto v = que.front();
            que.pop();
            for(auto to : g[v]) {
                if(dist[i][to] != inf) continue;
                dist[i][to] = dist[i][v] + 1;
                que.emplace(to);
            }
        }
    }

    int ans = (dist[s1][t1] <= l1 && dist[s2][t2] <= l2 ? dist[s1][t1] + dist[s2][t2] : inf);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(dist[s1][i] + dist[i][j] + dist[j][t1] <= l1) {
                if(dist[s2][i] + dist[i][j] + dist[j][t2] <= l2) {
                    ans = min(ans, dist[i][j] + dist[s1][i] + dist[j][t1] + dist[s2][i] + dist[j][t2]);
                }
                if(dist[t2][i] + dist[i][j] + dist[j][s2] <= l2) {
                    ans = min(ans, dist[i][j] + dist[s1][i] + dist[j][t1] + dist[t2][i] + dist[j][s2]);
                }
            }
        }
    }
    if(ans == inf) {
        cout << -1 << endl;
    } else {
        cout << m - ans << endl;
    }
}
