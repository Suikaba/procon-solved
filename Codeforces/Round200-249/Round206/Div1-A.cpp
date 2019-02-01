#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll inf = 1e18;

int main() {
    int n, l, r, ql, qr; cin >> n >> l >> r >> ql >> qr;
    vector<int> w(n);
    for(int i = 0; i < n; ++i) {
        cin >> w[i];
    }

    vector<ll> lsum(n + 1), rsum(n + 1);
    for(int i = 0; i < n; ++i) {
        lsum[i + 1] = lsum[i] + l * w[i];
        rsum[i + 1] = rsum[i] + r * w[i];
    }

    ll ans = inf;
    for(int mid = 0; mid <= n; ++mid) {
        const ll lcnt = mid, rcnt = n - mid;
        ll tans = lsum[mid] + rsum[n] - rsum[mid];
        if(lcnt - rcnt > 1) {
            tans += ql * (lcnt - rcnt - 1);
        }
        if(rcnt - lcnt > 1) {
            tans += qr * (rcnt - lcnt - 1);
        }
        ans = min(ans, tans);
    }

    cout << ans << endl;
}
