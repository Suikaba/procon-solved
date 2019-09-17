#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

constexpr ll inf = 1e18;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int m, n;
    while(cin >> m >> n) {
        vector<pll> p(n);
        for(auto& pp : p) cin >> pp.first >> pp.second;
        if(n & 1) {
            cout << -1 << endl;
            continue;
        }

        auto rotate = [&] () {
            for(auto& pp : p) {
                const ll x = pp.first, y = pp.second;
                pp.first = y, pp.second = m - 1 - x;
            }
        };

        auto solve = [&] () {
            sort(begin(p), end(p));
            ll tans = inf;
            priority_queue<ll> que;
            int it = 0;
            while(it < n) {
                const int fst = it;
                const ll x = p[fst].first;
                while(it < n && p[it].first == x) {
                    que.push(p[it++].second);
                }
                while((int)que.size() > n / 2 + 1) {
                    que.pop();
                }
                if((int)que.size() == n / 2 + 1) {
                    const ll tmp = que.top();
                    que.pop();
                    if(que.top() == tmp) {
                        que.push(tmp);
                    }
                }
                if((int)que.size() == n / 2) {
                    tans = min(tans, (que.top() + 1) * (x + 1));
                }
            }
            return tans;
        };

        ll ans = inf;
        for(int i = 0; i < 4; rotate(), ++i) {
            ans = min(ans, solve());
        }
        if(ans == inf) {
            cout << -1 << endl;
        } else {
            cout << ans << endl;
        }
    }
}
