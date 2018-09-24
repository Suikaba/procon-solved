#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int n, k; scanf("%d %d", &n, &k);
    vector<ll> a(n);
    for(int i = 0; i < n; ++i) {
        scanf("%lld", &a[i]);
    }
    ll ans = 0;
    map<ll, ll> cnt, cnt2;
    for(int i = n - 1; i >= 0; --i) {
        ans += cnt2[a[i] * k];
        cnt2[a[i]] += cnt[a[i] * k];
        cnt[a[i]] += 1;
    }
    printf("%lld\n", ans);
}
