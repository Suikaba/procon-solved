#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
    int n, k; cin >> n >> k;
    vector<int> x(n), y(n);
    for(int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }

    vector<tuple<short, short, short>> v;
    for(int i = 0; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {
            int dx = x[j] - x[i], dy = y[j] - y[i];
            if(dx == 0) {
                v.emplace_back(x[i] + 20000, 0, 0);
                continue;
            }
            if(dy == 0) {
                v.emplace_back(0, y[i], 0);
                continue;
            }
            if(dx < 0) dx *= -1, dy *= -1;
            const int g = __gcd(dx, abs(dy));
            dx /= g, dy /= g;
            int b = 0;
            if(x[i] < 0) {
                b = y[i] - (x[i] - dx + 1) / dx * dy;
            } else {
                b = y[i] - (x[i] / dx) * dy;
            }
            v.emplace_back(dx, dy, b);
        }
    }
    sort(begin(v), end(v));

    const int sz = v.size();
    bool ans = 0;
    int cnt = 1;
    for(int i = 0; i + 1 < sz; ++i) {
        if(v[i] == v[i + 1]) {
            cnt += 1;
        } else {
            ans |= cnt >= k * (k - 1) / 2;
            cnt = 1;
        }
    }
    ans |= cnt >= k * (k - 1) / 2;

    cout << ans << endl;
}
