#include <bits/stdc++.h>
using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2558

// 反省点
// バグらせすぎなんだよね．枝刈り慣れてないし仕方ないのか？
// move したあとのデータにアクセスしてて死んでた．中途半端にやるくらいならコピーして良さそう．
// 実装方針はある意味では間違ってない気がする．速度重視ならこれぐらい書く必要ありそう．．
// 実装時間優先なら，どれかの戦略を省いてコード量削減か．難しい．

using pii = pair<int, int>;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<set<int>> g(n);
    vector<int> deg(n);
    for(int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        g[a - 1].insert(b - 1);
        g[b - 1].insert(a - 1);
        deg[a - 1]++;
        deg[b - 1]++;
    }

    vector<bool> used(n);
    int now = 0;
    for(int i = 0; i < n; ++i) {
        if(deg[i] > k) {
            used[i] = true;
            deg[i] = 0;
            now++;
            for(auto to : g[i]) {
                deg[to]--;
            }
        }
    }
    int remain_edge = 0;
    for(int i = 0; i < n; ++i) {
        remain_edge += deg[i];
    }
    remain_edge /= 2;
    if(now > k) {
        cout << "Impossible" << endl;
        return 0;
    }

    vector<int> ord;
    {
        vector<set<int>> g2(n - now);
        deg.assign(n - now, 0);
        int x = 0;
        vector<int> idx(n);
        vector<pii> deg_idx;
        for(int i = 0; i < n; ++i) {
            if(used[i]) continue;
            deg[x] = 0;
            idx[i] = x++;
        }
        for(int i = 0; i < n; ++i) {
            if(used[i]) continue;
            for(auto to : g[i]) {
                if(!used[to]) {
                    deg[idx[i]]++;
                    g2[idx[i]].insert(idx[to]);
                }
            }
            deg_idx.emplace_back(deg[idx[i]], idx[i]);
        }
        sort(rbegin(deg_idx), rend(deg_idx));
        for(auto& p : deg_idx) {
            ord.push_back(p.second);
        }
        g = move(g2);
        n = g.size();
    }

    int ans = k + 1;
    function<void(int)> solve = [&](int i) {
        if(i == n) {
            ans = min(ans, now);
            return;
        }
        const int r = min(k - now, n - i);
        const int v = ord[i];
        if(now >= ans || now > k || remain_edge > r * deg[v]) {
            return;
        };
        if(g[v].empty()) {
            solve(i + 1);
        } else {
            // use
            if((int)g[v].size() > 1) {
                now++;
                vector<int> erased;
                for(auto to : g[v]) {
                    erased.push_back(to);
                    g[to].erase(v);
                }
                remain_edge -= (int)g[v].size();
                g[v].clear();
                solve(i + 1);
                for(auto to : erased) {
                    g[v].insert(to);
                    g[to].insert(v);
                }
                remain_edge += (int)g[v].size();
                now--;
            }

            // not use
            if(now + (int)g[v].size() <= min(ans, k)) {
                now += g[v].size();
                vector<int> erased;
                vector<set<int>> erased2;
                set<pii> erased_edges;
                for(auto to : g[v]) {
                    erased.push_back(to);
                    set<int> tmp;
                    for(auto to2 : g[to]) {
                        tmp.insert(to2);
                        erased_edges.emplace(min(to, to2), max(to, to2));
                        if(to2 != v) {
                            g[to2].erase(to);
                        }
                    }
                    g[to].clear();
                    erased2.push_back(move(tmp));
                }
                remain_edge -= erased_edges.size();
                g[v].clear();
                solve(i + 1);
                for(int j = 0; j < (int)erased.size(); ++j) {
                    g[v].insert(erased[j]);
                    for(auto to2 : erased2[j]) {
                        g[to2].insert(erased[j]);
                    }
                    g[erased[j]] = move(erased2[j]);
                    remain_edge += g[erased[j]].size();
                }
                now -= g[v].size();
            }
        }
    };
    solve(0);

    if(ans > k) {
        cout << "Impossible" << endl;
    } else {
        cout << ans << endl;
    }
}
