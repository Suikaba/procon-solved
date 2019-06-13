#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ll n, k; cin >> n >> k;

    int ans = 0, sum = 0;
    while(n >= max(1LL, (sum + k - 1) / k)) {
        ans += 1;
        const ll add = max(1LL, (sum + k - 1) / k);
        sum += add;
        n -= add;
    }

    cout << ans << endl;
}
