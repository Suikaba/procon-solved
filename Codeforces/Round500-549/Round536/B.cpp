#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll, int>;

int main() {
    int n, m; cin >> n >> m;
    vector<ll> a(n), c(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    priority_queue<pll, vector<pll>, greater<>> que;
    for(int i = 0; i < n; ++i) {
        cin >> c[i];
        que.emplace(c[i], i);
    }

    vector<ll> ans(m);
    for(int i = 0; i < m; ++i) {
        ll t, d; cin >> t >> d;
        t--;
        if(a[t] < d) {
            ans[i] = a[t] * c[t];
            ll rest = d - a[t];
            a[t] = 0;
            while(!que.empty() && rest > 0) {
                auto p = que.top(); que.pop();
                const int idx = p.second;
                const ll use = min(a[idx], rest);
                ans[i] += use * c[idx];
                a[idx] -= use;
                rest -= use;
                if(a[idx] > 0) {
                    que.emplace(c[idx], idx);
                }
            }
            if(rest > 0) {
                ans[i] = 0;
            }
        } else {
            ans[i] = d * c[t];
            a[t] -= d;
        }
    }

    for(int i = 0; i < m; ++i) {
        cout << ans[i] << "\n";
    }
}
