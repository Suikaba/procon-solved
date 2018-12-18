#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int big_sz = 500;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int n, m, q; cin >> n >> m >> q;
    vector<ll> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<vector<int>> s(m);
    vector<ll> sum(m);
    vector<int> big_idx;
    vector<vector<bool>> have(256, vector<bool>(n));
    for(int i = 0; i < m; ++i) {
        int sz; cin >> sz;
        s[i].resize(sz);
        if(sz >= big_sz) {
            big_idx.push_back(i);
        }
        for(int j = 0; j < sz; ++j) {
            cin >> s[i][j];
            s[i][j]--;
            sum[i] += a[s[i][j]];
            if(sz >= big_sz) {
                have[big_idx.size() - 1][s[i][j]] = true;
            }
        }
    }

    vector<vector<int>> common_cnt(m, vector<int>(big_idx.size()));
    for(int i = 0; i < m; ++i) {
        if((int)s[i].size() >= big_sz) continue;
        for(auto j : s[i]) {
            for(int k = 0; k < (int)big_idx.size(); ++k) {
                common_cnt[i][k] += have[k][j];
            }
        }
    }

    vector<ll> add(m);
    while(q--) {
        char kind; cin >> kind;
        if(kind == '+') {
            int idx; ll x; cin >> idx >> x;
            idx--;
            if(s[idx].size() < big_sz) {
                for(auto j : s[idx]) {
                    a[j] += x;
                }
                for(int i = 0; i < (int)big_idx.size(); ++i) {
                    sum[big_idx[i]] += x * common_cnt[idx][i];
                }
            } else {
                add[idx] += x;
            }
        } else {
            int idx; cin >> idx;
            idx--;
            ll ans = 0;
            if((int)s[idx].size() < big_sz) {
                for(int i = 0; i < (int)big_idx.size(); ++i) {
                    ans += common_cnt[idx][i] * add[big_idx[i]];
                }
                for(auto j : s[idx]) {
                    ans += a[j];
                }
            } else {
                ans = sum[idx] + add[idx] * s[idx].size();
            }
            cout << ans << endl;
        }
    }
}
