#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll inf = 1e18;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i] = __builtin_popcountll(a[i]);
    }
    vector<int> pari(n + 1);
    for(int i = 0; i < n; ++i) {
        pari[i + 1] = pari[i] ^ (a[i] & 1);
    }

    ll ans = 0;
    {
        const ll cnt0 = count(begin(pari), end(pari), 0), cnt1 = n + 1 - cnt0;
        ans += cnt0 * (cnt0 - 1) / 2 + cnt1 * (cnt1 - 1) / 2;
    }
    for(int i = 0; i < n; ++i) {
        int tpari = 0;
        ll ma = 0, sum = 0;
        for(int j = i; j >= max(0, i - 64); --j) {
            tpari ^= a[j] & 1;
            ma = max(ma, a[j]);
            sum += a[j];
            ans -= (!tpari && sum < ma * 2);
        }
    }

    cout << ans << endl;
}