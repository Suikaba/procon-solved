
// http://codeforces.com/contest/1012/problem/A

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll inf = 2e18;

ll solve(vector<ll> const& a) {
    const int n = a.size();
    ll ans = (a.back() - a[n / 2]) * (a[n / 2 - 1] - a[0]);
    for(int i = 1; i + n / 2 < n; ++i) {
        ans = min(ans, (a.back() - a[0]) * (a[i + n / 2 - 1] - a[i]));
    }
    return ans;
}

int main() {
    int n;
    cin >> n;
    n *= 2;
    vector<ll> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(begin(a), end(a));
    cout << solve(a) << endl;
}
