#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k; cin >> n >> k;
    int ans = 0;
    for(int i = 0; i < n; ++i) {
        int a; cin >> a;
        vector<bool> v(10);
        while(a > 0) {
            v[a % 10] = true;
            a /= 10;
        }
        ans += count(begin(v), begin(v) + k + 1, true) == k + 1;
    }
    cout << ans << endl;
}
