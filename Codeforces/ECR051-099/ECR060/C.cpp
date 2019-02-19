#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll inf = 2e18;

int main() {
    ll sx, sy, gx, gy; cin >> sx >> sy >> gx >> gy;
    int n; cin >> n;
    string s; cin >> s;
    const ll dx = gx - sx, dy = gy - sy;

    const string dir = "UDLR";
    vector<vector<ll>> cnt(n + 1, vector<ll>(4));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < 4; ++j) {
            cnt[i + 1][j] = cnt[i][j] + (s[i] == dir[j]);
        }
    }

    ll lb = -1, ub = inf;
    while(ub - lb > 1) {
        const auto mid = (ub + lb) >> 1;
        vector<ll> sum(4);
        for(int i = 0; i < 4; ++i) {
            sum[i] = cnt[n][i] * (mid / n) + cnt[mid % n][i];
        }
        const ll hsum = sum[3] - sum[2];
        const ll vsum = sum[0] - sum[1];
        if(abs(hsum - dx) + abs(vsum - dy) <= mid) {
            ub = mid;
        } else {
            lb = mid;
        }
    }

    if(ub == inf) {
        cout << -1 << endl;
    } else {
        cout << ub << endl;
    }
}
