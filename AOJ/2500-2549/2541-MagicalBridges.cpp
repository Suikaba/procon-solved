#include <bits/stdc++.h>
using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2541

// 反省点
// d[s][i] == inf のときに弾くのを忘れていた．
// 二分探索パートはうまくやればサボれるかも？サボるための処理を書くのと
// 二分探索するのどっちが楽かわからないけど．

using ll = long long;

constexpr ll inf = 1e18;

struct edge {
    int to;
    ll cost;
    bool magical;
};

using edges = vector<edge>;
using graph = vector<edges>;

int main() {
    int n, m, s1, s2, t;
    while(cin >> n >> m >> s1 >> s2 >> t, n) {
        s1--; s2--; t--;
        graph g(n);
        int mag_num = 0;
        for(int i = 0; i < m; ++i) {
            int a, b;
            string w;
            cin >> a >> b >> w;
            ll c = (w == "x" ? 0 : stoi(w));
            mag_num += (w == "x");
            bool mag = w == "x";
            g[a - 1].push_back(edge{b - 1, c, mag});
            g[b - 1].push_back(edge{a - 1, c, mag});
        }

        vector<vector<ll>> d(n, vector<ll>(mag_num + 1, inf));
        d[t][0] = 0;
        using node = tuple<ll, int, int>;
        priority_queue<node, vector<node>, greater<node>> que;
        que.emplace(0, t, 0);
        while(!que.empty()) {
            ll cur_d;
            int v, mag_cnt;
            tie(cur_d, v, mag_cnt) = que.top();
            que.pop();
            if(cur_d > d[v][mag_cnt]) continue;
            for(auto& e : g[v]) {
                const ll nxt_d = cur_d + e.cost;
                const int nxt_cnt = mag_cnt + e.magical;
                if(nxt_cnt > mag_num || d[e.to][nxt_cnt] <= nxt_d) continue;
                que.emplace(nxt_d, e.to, nxt_cnt);
                d[e.to][nxt_cnt] = nxt_d;
            }
        }

        vector<ll> l1(mag_num + 1), r1(mag_num + 1, inf); // [l1, r1]
        vector<ll> l2(mag_num + 1), r2(mag_num + 1, inf);
        auto calc_lr = [mag_num, &d](int s, vector<ll>& l, vector<ll>& r) {
            for(int i = 0; i < mag_num + 1; ++i) {
                for(int j = 0; j < mag_num + 1; ++j) {
                    if(i == j) continue;
                    if(j - i < 0) {
                        ll t = 0;
                        if(d[s][i] - d[s][j] <= 0) {
                            t = (d[s][i] - d[s][j]) / (j - i);
                        } else {
                            t = -1;
                        }
                        r[i] = min(r[i], t);
                    } else {
                        l[i] = max(l[i], (d[s][i] - d[s][j] + (j - i) - 1) / (j - i));
                    }
                }
            }
        };
        calc_lr(s1, l1, r1);
        calc_lr(s2, l2, r2);

        ll ans = inf;
        for(int i = 0; i < mag_num + 1; ++i) {
            for(int j = 0; j < mag_num + 1; ++j) {
                if(d[s1][i] == inf || d[s2][j] == inf) continue;
                ll lb = max(l1[i], l2[j]);
                ll ub = min(r1[i], r2[j]);
                if(lb > ub) continue;
                while(ub - lb > 1) {
                    const ll mid = (lb + ub) / 2;
                    ll c1 = d[s1][i] + mid * i;
                    ll c2 = d[s2][j] + mid * j;
                    if(c1 < c2) {
                        if(i < j) ub = mid;
                        else      lb = mid;
                    } else {
                        if(i < j) lb = mid;
                        else      ub = mid;
                    }
                }
                ll c1 = abs(d[s1][i] + lb * i - (d[s2][j] + lb * j));
                ll c2 = abs(d[s1][i] + ub * i - (d[s2][j] + ub * j));
                ans = min({ans, c1, c2});
            }
        }
        cout << ans << endl;
    }
}
