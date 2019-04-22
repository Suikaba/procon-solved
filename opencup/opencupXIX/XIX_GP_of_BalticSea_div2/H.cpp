#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int n; cin >> n;
    vector<int> p(n), cnt(n + 1);
    for(int i = 0; i < n; ++i) {
        cin >> p[i];
        cnt[p[i]] += 1;
    }

    ll ans = 0;
    for(int i = n - 1; i >= 0; --i) {
        cnt[p[i]] -= 1;
        for(int j = p[i]; j <= n; j += p[i]) {
            ans += cnt[j];
        }
    }

    cout << ans << endl;
}