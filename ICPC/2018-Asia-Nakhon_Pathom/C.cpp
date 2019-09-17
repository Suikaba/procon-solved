#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, w; cin >> n >> w;
    vector<int> h(n);
    for(int i = 0; i < n; ++i) {
        cin >> h[i];
    }
    vector<int> ord(n);
    iota(begin(ord), end(ord), 0);
    sort(begin(ord), end(ord), [&] (int i, int j) { return h[i] < h[j]; });

    vector<int> dp(n);
    for(auto i : ord) {
        for(int j = max(i - w, 0); j < min(i + w + 1, n); ++j) {
            if(h[i] >= h[j]) continue;
            dp[j] = max(dp[j], dp[i] + 1);
        }
    }

    cout << *max_element(begin(dp), end(dp)) << endl;
}
