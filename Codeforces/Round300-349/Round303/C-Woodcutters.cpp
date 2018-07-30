#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 2e9;

int main() {
    int n;
    cin >> n;
    vector<int> x(n), h(n);
    for(int i = 0; i < n; ++i) {
        cin >> x[i] >> h[i];
    }
    int ans = 0;
    int prev = inf;
    for(int i = 0; i < n - 1; ++i) {
        if(prev > h[i]) {
            ans += 1;
            prev = x[i + 1] - x[i];
        } else if(x[i + 1] - x[i] > h[i]) {
            ans += 1;
            prev = x[i + 1] - x[i] - h[i];
        } else {
            prev = x[i + 1] - x[i];
        }
    }
    ans += 1;
    cout << ans << endl;
}
