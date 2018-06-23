#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    int sum = 0;
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i] *= 10;
        sum += a[i];
    }
    sort(begin(a), end(a));
    int need = 45 * n - sum;
    int ans = 0, idx = 0;
    while(need > 0) {
        need -= (50 - a[idx++]);
        ans += 1;
    }
    cout << ans << endl;
}
