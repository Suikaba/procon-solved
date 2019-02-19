#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    const int maxi = *max_element(begin(a), end(a));
    vector<int> dp(n + 1);
    for(int i = 0; i < n; ++i) {
        dp[i + 1] = (a[i] != maxi ? 0 : dp[i] + 1);
    }

    cout << *max_element(begin(dp), end(dp)) << endl;
}
