#include <bits/stdc++.h>
using namespace std;

// http://codeforces.com/contest/992/problem/C

// 反省点
// 条件書き間違えが多発．根気よく詰める訓練するしかなさそう．
// こういう問題いつも適当にやってWAもらってから考えてるので，それが原因なんだよなあ．

using ll = long long;

int main() {
    ll l, r, x, y;
    cin >> l >> r >> x >> y; // x : gcd
    if(y % x != 0) {
        cout << 0 << endl;
    } else {
        y /= x;
        vector<ll> v;
        for(ll z = 2; z * z <= y; ++z) {
            if(y % z == 0) {
                ll t = 1;
                while(y % z == 0) {
                    y /= z;
                    t *= z;
                }
                v.push_back(t);
            }
        }
        if(y > 1) v.push_back(y);

        if(v.size() == 0) {
            cout << (l <= x && x <= r) << endl;
            return 0;
        }

        ll ans = 0;
        const int n = v.size();
        assert(n <= 26);
        for(int S = 0; S < (1 << n); ++S) {
            ll v1 = 1, v2 = 1;
            for(int i = 0; i < n; ++i) {
                if(S & (1 << i)) v1 *= v[i];
                else v2 *= v[i];
            }
            assert(v1 >= 0 && v2 >= 0 && __gcd(v1, v2) == 1);
            ans += (l <= x * v1 && x * v1 <= r && l <= x * v2 && x * v2 <= r);
        }

        cout << ans << endl;
    }
}
