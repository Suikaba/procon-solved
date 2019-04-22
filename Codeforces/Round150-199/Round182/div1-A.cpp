#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
    int n; cin >> n;
    vector<int> a(2 * n - 1);
    int neg = 0;
    for(int i = 0; i < 2 * n - 1; ++i) {
        cin >> a[i];
        neg += a[i] < 0;
    }
    vector<vector<bool>> can(2 * n, vector<bool>(2 * n));
    can[neg][2 * n - 1 - neg] = true;
    queue<pii> que;
    que.emplace(neg, 2 * n - 1 - neg);
    while(!que.empty()) {
        auto [neg, pos] = que.front();
        que.pop();
        for(int use = 0; use <= min(neg, n); ++use) {
            if(pos < n - use) continue;
            const int nneg = neg - use + (n - use);
            const int npos = pos - (n - use) + use;
            if(can[nneg][npos]) continue;
            can[nneg][npos] = true;
            que.emplace(nneg, npos);
        }
    }

    sort(begin(a), end(a), [] (int a, int b) { return abs(a) < abs(b); });
    int ans = accumulate(begin(a), end(a), 0);
    for(int i = 0; i <= 2 * n - 1; ++i) {
        if(can[i][2 * n - 1 - i]) {
            int tans = 0;
            for(int j = 0; j < i; ++j) {
                tans -= abs(a[j]);
            }
            for(int j = 0; j < 2 * n - 1 - i; ++j) {
                tans += abs(a[2 * n - 2 - j]);
            }
            ans = max(ans, tans);
        }
    }
    cout << ans << endl;
}