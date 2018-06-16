#include <bits/stdc++.h>
using namespace std;

// http://codeforces.com/problemset/problem/650/A

// 反省点：なし

using ll = long long;
using pii = pair<int, int>;

int main() {
    int n;
    cin >> n;
    vector<ll> x(n), y(n);
    map<int, ll> cnt_x, cnt_y;
    map<pii, ll> same;
    for(int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
        cnt_x[x[i]]++;
        cnt_y[y[i]]++;
        same[make_pair(x[i], y[i])]++;
    }

    ll ans = 0;
    for(auto& p : cnt_x) {
        ans += p.second * (p.second - 1) / 2;
    }
    for(auto& p : cnt_y) {
        ans += p.second * (p.second - 1) / 2;
    }
    for(auto& p : same) {
        ans -= p.second * (p.second - 1) / 2;
    }

    cout << ans << endl;
}
