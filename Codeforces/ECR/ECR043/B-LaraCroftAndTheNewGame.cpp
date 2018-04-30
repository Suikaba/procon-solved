#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

int main() {
    ll n, m, k;
    cin >> n >> m >> k;
    if(k < n) {
        cout << k + 1 << ' ' << 1 << endl;
    } else {
        const ll r = k - n;
        int y = n - max(r / (m - 1), 0LL);
        int diff_x = r - (n - y) * (m - 1);
        int x = (y & 1 ? m - diff_x : diff_x + 2);
        cout << y << ' ' << x << endl;
    }
}
