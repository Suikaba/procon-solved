#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ll n, m; cin >> n >> m;
    string x, y; cin >> x >> y;

    const ll g = __gcd(x.size(), y.size());
    const ll lcm = x.size() / g * y.size();
    vector<vector<ll>> cnt(g, vector<ll>(26));
    for(int i = 0; i < (int)x.size(); ++i) {
        cnt[i % g][x[i] - 'a'] += 1;
    }

    ll ans = 0;
    for(int i = 0; i < (int)y.size(); ++i) {
        for(int j = 0; j < 26; ++j) {
            if(y[i] == 'a' + j) continue;
            ans += cnt[i % g][j];
        }
    }
    ans *= n * x.size() / lcm;

    cout << ans << endl;
}