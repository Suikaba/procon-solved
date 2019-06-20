#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

constexpr ll inf = 1e18;

int main() {
    int n; cin >> n;
    vector<ll> a(n);
    for(auto& aa : a) cin >> aa;

    vector<map<ll, int>> dp(n + 1);
    vector<map<ll, pair<ll, int>>> pre(n + 1);
    dp[0][-inf] = 0;
    for(int i = 0; i < n; ++i) {
        ll sum = 0;
        for(int j = i + 1; j <= n; ++j) {
            sum += a[j - 1];
            auto it = dp[i].lower_bound(sum);
            if(it == dp[i].begin()) continue;
            it = prev(it);
            { // update
                auto nit = dp[j].lower_bound(sum);
                while(nit != end(dp[j]) && nit->second <= it->second + 1) {
                    pre[j].erase(nit->first);
                    nit = dp[j].erase(nit);
                }
                if(nit == begin(dp[j]) || prev(nit)->second < it->second + 1) {
                    dp[j][sum] = it->second + 1;
                    pre[j][sum] = {it->first, i};
                }
            }
        }
    }

    int max_len = 0;
    ll cur_sum = 0, cur_idx = n;
    for(auto const& p : dp[n]) {
        if(max_len < p.second) {
            max_len = p.second;
            cur_sum = p.first;
        }
    }
    vector<int> ans;
    while(pre[cur_idx].count(cur_sum)) {
        const auto p = pre[cur_idx][cur_sum];
        ans.push_back(p.second);
        cur_sum = p.first, cur_idx = p.second;
    }
    ans.pop_back();
    reverse(begin(ans), end(ans));

    cout << ans.size() + 1 << endl;
    for(int i = 0; i < (int)ans.size(); ++i) {
        cout << ans[i] << " \n"[i + 1 == (int)ans.size()];
    }
}
