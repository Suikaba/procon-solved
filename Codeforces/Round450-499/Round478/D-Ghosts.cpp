#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ll n, a, b;
    cin >> n >> a >> b;
    vector<ll> x(n), vx(n), vy(n);
    map<ll, ll> cnt;
    vector<int> stop_zero, right_zero, left_zero;
    map<pair<ll, ll>, ll> same;
    for(int i = 0; i < n; ++i) {
        scanf("%lld %lld %lld", &x[i], &vx[i], &vy[i]);
        //cout << vx[i] << ' ' << vy[i] << ' ' << a * vx[i] - vy[i] << endl;
        if(a * vx[i] - vy[i] == 0) {
            if(vx[i] == 0 && vy[i] == 0) {
                stop_zero.push_back(x[i]);
            } else if(vx[i] > 0) {
                right_zero.push_back(x[i]);
            } else if(vx[i] < 0) {
                left_zero.push_back(x[i]);
            }
        } else {
            same[make_pair(vx[i], vy[i])] ++;
            cnt[a * vx[i] - vy[i]] += 1;
        }
    }

    ll ans = 0;
    for(auto& p : cnt) {
        ans += p.second * (p.second - 1);
    }
    ans += 1LL * (right_zero.size() + left_zero.size()) * stop_zero.size() * 2
        + 1LL * right_zero.size() * left_zero.size() * 2;
    for(auto& p : same) {
        ans -= p.second * (p.second - 1);
    }

    cout << ans << endl;
}
