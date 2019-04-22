#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int n; cin >> n;
    vector<int> m(n);
    for(int i = 0; i < n; ++i) {
        cin >> m[i];
    }

    ll cur = 0;
    vector<ll> need(n);
    for(int i = 0; i < n; ++i) {
        cur = max(cur, m[i] + 1LL);
        need[i] = cur;
    }
    for(int i = n - 2; i >= 0; --i) {
        need[i] = max(need[i], need[i + 1] - 1);
    }

    ll ans = 0;
    for(int i = 0; i < n; ++i) {
        ans += need[i] - m[i] - 1;
    }
    cout << ans << endl;
}