#include <bits/stdc++.h>
using namespace std;

// 反省点
// 普通に考察できなかった．うーん．
// そういえば https://beta.atcoder.jp/contests/arc097/tasks/arc097_a と発想が全く同じなんですねえ．

using ll = long long;

constexpr ll inf = numeric_limits<ll>::max();

int main() {
    ll n, k;
    cin >> n >> k;
    vector<ll> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<ll> nxt_pos_not_one(n, inf);
    for(int i = n - 1; i >= 1; --i) {
        if(i == n - 1 || a[i] != 1) {
            nxt_pos_not_one[i - 1] = i;
        } else {
            nxt_pos_not_one[i - 1] = nxt_pos_not_one[i];
        }
    }

    auto check_ovf = [&](ll p, ll x) {
        return inf / p > x;
    };

    int ans = 0;
    for(int i = 0; i < n; ++i) {
        ll p = a[i], sum = a[i];
        int r = i;
        ans += sum * k == p;
        while(nxt_pos_not_one[r] < n && check_ovf(p, a[nxt_pos_not_one[r]])) {
            int nr = nxt_pos_not_one[r];
            ans += (p % k == 0 && k * sum < p && p <= (sum + nr - r - 1) * k);
            p *= a[nr];
            sum += nr - r - 1 + a[nr];
            ans += k * sum == p;
            r = nr;
        }
    }

    cout << ans << endl;
}
