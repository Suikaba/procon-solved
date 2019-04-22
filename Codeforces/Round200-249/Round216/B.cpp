#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k, l, r, sall, sk; cin >> n >> k >> l >> r >> sall >> sk;

    vector<int> a(n);
    for(int i = 0; i < k; ++i) {
        a[i] = sk / k;
        if(sk % k >= i + 1) a[i] += 1;
    }
    int sum = sk + (n - k) * l;
    for(int i = k; i < n; ++i) {
        a[i] = min(a[i - 1], l + (sall - sum));
        sum += a[i] - l;
    }

    for(int i = 0; i < n; ++i) {
        assert(l <= a[i] && a[i] <= r && (i == 0 || a[i - 1] >= a[i]) && sum == sall);
        cout << a[i] << " \n"[i + 1 == n];
    }
}
