#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int n, q;
    cin >> n >> q;
    vector<ll> a(n), k(q);
    for(int i = 0; i < n; ++i) {
        scanf("%lld", &a[i]);
    }
    for(int i = 0; i < q; ++i) {
        scanf("%lld", &k[i]);
    }

    vector<ll> sum(n + 1);
    for(int i = 0; i < n; ++i) {
        sum[i + 1] = sum[i] + a[i];
    }

    int ans = n;
    ll current_pos_a = a[0];
    int current_pos = 1;
    for(auto x : k) {
        if(current_pos_a <= x) {
            x -= current_pos_a;
            int idx = upper_bound(begin(sum), end(sum), x + sum[current_pos]) - begin(sum);
            if(idx == n + 1) {
                ans = n;
                current_pos = 1;
                current_pos_a = a[0];
            } else {
                ans = n - idx + 1;
                current_pos_a = sum[idx] - (x + sum[current_pos]);
                current_pos = idx;
            }
        } else {
            current_pos_a -= x;
        }

        cout << ans << endl;
    }
}
