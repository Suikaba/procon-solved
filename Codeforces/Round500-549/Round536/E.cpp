#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

constexpr ll inf = 1e18;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m, k; cin >> n >> m >> k;
    vector<int> s(k), t(k), d(k), w(k);
    vector<vector<int>> add(n + 1), rm(n + 1);
    for(int i = 0; i < k; ++i) {
        cin >> s[i] >> t[i] >> d[i] >> w[i];
        s[i]--, t[i]--;
        add[s[i]].push_back(i);
        rm[t[i] + 1].push_back(i);
    }
    vector<pii> max_val(n + 1, make_pair(-1, -1));
    multiset<pii, greater<>> cur;
    for(int i = 0; i < n; ++i) {
        for(auto j : add[i]) {
            cur.emplace(w[j], d[j]);
        }
        for(auto j : rm[i]) {
            auto it = cur.lower_bound(make_pair(w[j], d[j]));
            cur.erase(it);
        }
        if(cur.empty()) continue;
        max_val[i] = *cur.begin();
    }

    vector<vector<ll>> dp(n + 1, vector<ll>(m + 1, inf));
    dp[0][0] = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j <= m; ++j) {
            if(max_val[i].first == -1) {
                dp[i + 1][j] = min(dp[i + 1][j], dp[i][j]);
                continue;
            }
            const int to = max_val[i].second;
            dp[to][j] = min(dp[to][j], dp[i][j] + max_val[i].first); // not disturb
            if(j != m) {
                dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j]); // disturb
            }
        }
    }

    cout << *min_element(begin(dp[n]), end(dp[n])) << endl;
}
