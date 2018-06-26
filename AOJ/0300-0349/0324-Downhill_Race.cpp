#include <bits/stdc++.h>
using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0324

// 反省点
// トポロジカル順序書いたのに使ってなくてWAはやしてるのは最悪．
// なんか前処理を function で宣言したはいいけど使い忘れる，みたいなの多いので注意．
// あとダイクストラで解いたけど，DPで書くという選択肢をちゃんと持とう．

using ll = long long;

constexpr ll inf = 1e18;

struct edge {
    int to;
    ll c1, c2;
};

using edges = vector<edge>;
using graph = vector<edges>;

int main() {
    int n, p;
    cin >> n >> p;
    graph g(n);
    for(int i = 0; i < p; ++i) {
        int s, e;
        ll t1, t2;
        cin >> s >> e >> t1 >> t2;
        g[s - 1].push_back(edge{e - 1, t1, t2});
    }

    vector<int> topo(n, -1);
    int idx = 0;
    function<void(int)> calc_topo = [&] (int v) {
        if(topo[v] != -1) return;
        for(auto& e : g[v]) {
            calc_topo(e.to);
        }
        topo[v] = idx++;
    };
    calc_topo(0);

    vector<vector<ll>> dist(n, vector<ll>(n, inf));
    dist[0][0] = 0;
    using state = tuple<ll, int, int>;
    priority_queue<state, vector<state>, greater<state>> que;
    que.emplace(0, 0, 0);
    while(!que.empty()) {
        ll cur_c;
        int fst_v, sec_v;
        tie(cur_c, fst_v, sec_v) = que.top();
        que.pop();
        if(fst_v == sec_v) {
            for(auto& e : g[fst_v]) {
                ll nxt_c = cur_c + e.c1 + e.c2;
                if(dist[e.to][e.to] > nxt_c) {
                    dist[e.to][e.to] = nxt_c;
                    que.emplace(nxt_c, e.to, e.to);
                }
            }

            for(auto& e1 : g[fst_v]) {
                for(auto& e2 : g[sec_v]) {
                    if(e1.to == e2.to) continue;
                    ll nxt_c = cur_c + e1.c1 + e2.c1;
                    if(dist[e1.to][e2.to] > nxt_c) {
                        dist[e1.to][e2.to] = nxt_c;
                        que.emplace(nxt_c, e1.to, e2.to);
                    }
                }
            }
        } else {
            if(topo[fst_v] > topo[sec_v]) {
                for(auto& e : g[fst_v]) {
                    ll nxt_c = cur_c + e.c1;
                    if(dist[e.to][sec_v] > nxt_c) {
                        dist[e.to][sec_v] = nxt_c;
                        que.emplace(nxt_c, e.to, sec_v);
                    }
                }
            } else {
                for(auto& e : g[sec_v]) {
                    ll nxt_c = cur_c + e.c1;
                    if(dist[fst_v][e.to] > nxt_c) {
                        dist[fst_v][e.to] = nxt_c;
                        que.emplace(nxt_c, fst_v, e.to);
                    }
                }
            }
        }
    }

    cout << dist[n - 1][n - 1] << endl;
}
