#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll inf = 1e18;

int main() {
    ll s, t, d; cin >> s >> t >> d;
    vector<ll> w(d), sum(d + 1);
    for(int i = 0; i < d; ++i) {
        cin >> w[i];
        sum[i + 1] = sum[i] + w[i];
    }

    ll mini = inf;
    for(int i = 0; i <= d; ++i) {
        if(s + sum[i] <= t) {
            cout << i << endl;
            return 0;
        }
        mini = min(mini, sum[i]);
    }

    if(sum[d] >= 0) {
        cout << -1 << endl;
        return 0;
    }

    const ll cnt = (s - t + mini - sum[d] - 1) / (-sum[d]);
    ll ans = cnt * d;
    s += cnt * sum[d];
    for(int i = 0; i <= d; ++i) {
        if(s + sum[i] <= t) {
            ans += i;
            break;
        }
    }

    cout << ans << endl;
}