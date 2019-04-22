#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> s(n);
    for(int i = 0; i < n; ++i) {
        cin >> s[i];
    }

    vector<pair<int, vector<int>>> dp(n);
    for(int i = 0; i <= n - 1; ++i) {
        vector<int> vv = {s[i]};
        dp[i] = make_pair(0, vv);
    }
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < i; ++j) {
            auto v = dp[j].second;
            const int nval = dp[j].first + (v.back() == s[i]);
            if(dp[i].first <= nval) {
                v.push_back(s[i]);
                dp[i] = make_pair(nval, v);
            }
        }
    }

    pair<int, vector<int>> ans = make_pair(0, vector<int>{});
    for(int i = 0; i < n; ++i) {
        if(ans.first <= dp[i].first) {
            ans = dp[i];
        }
    }

    const int sz = ans.second.size();
    cout << ans.second.size() << " " << ans.first << endl;
    for(int i = 0; i < sz; ++i) {
        cout << ans.second[i] << " \n"[i + 1 == sz];
    }
}