#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int n; cin >> n;
    vector<int> a(n);
    for(auto& aa : a) cin >> aa;

    vector<int> inc(n, 1), deg(n, 1);
    for(int i = n - 2; i >= 0; --i) {
        if(a[i] <= a[i + 1]) {
            inc[i] = inc[i + 1] + 1;
        }
        if(a[i] > a[i + 1]) {
            deg[i] = deg[i + 1] + 1;
        }
    }

    vector<pii> ans(n + 1);
    for(int len = 1; len <= n; ++len) {
        for(int j = 0; j < n;) {
            ans[len].first += 1;
            ans[len].second += max(0, min(len, n - j) - max(inc[j], deg[j]));
            j += max({len, inc[j], deg[j]});
        }
    }

    int q; cin >> q;
    while(q--) {
        int run; cin >> run;
        cout << ans[run].first << " " << ans[run].second << "\n";
    }
}
