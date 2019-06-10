#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
constexpr ll inf = 1e18;

int main() {
    ifstream ifs("evacuation.in");
    int n; ifs >> n;
    vector<pii> p(n);
    for(int i = 0; i < n; ++i) {
        ifs >> p[i].first;
        p[i].second = i;
    }
    int m; ifs >> m;
    vector<pii> s(m);
    for(int i = 0; i < m; ++i) {
        ifs >> s[i].first;
        s[i].second = i + 1;
    }
    sort(begin(p), end(p));
    sort(begin(s), end(s));

    vector<vector<ll>> dp(n + 1, vector<ll>(m + 1, inf));
    vector<vector<int>> prev(n + 1, vector<int>(m + 1, -1));
    dp[0][0] = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j <= m; ++j) {
            if(j != 0 && dp[i + 1][j] > dp[i][j] + abs(p[i].first - s[j - 1].first)) { // same
                dp[i + 1][j] = dp[i][j] + abs(p[i].first - s[j - 1].first);
                prev[i + 1][j] = j;
            }
            if(j != m && dp[i + 1][j + 1] > dp[i][j] + abs(p[i].first - s[j].first)) { // next
                dp[i + 1][j + 1] = dp[i][j] + abs(p[i].first - s[j].first);
                prev[i + 1][j + 1] = j;
            }
        }
    }

    vector<int> ans(n);
    {
        int cur = m;
        for(int i = n - 1; i >= 0; --i) {
            ans[p[i].second] = s[cur - 1].second;
            cur = prev[i + 1][cur];
            assert(cur != -1);
        }
    }

    ofstream ofs("evacuation.out");
    ofs << dp[n][m] << endl;
    for(int i = 0; i < n; ++i) {
        ofs << ans[i] << " \n"[i + 1 == n];
    }
}
