#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    string s; cin >> s;
    reverse(begin(s), end(s));
    reverse(begin(a), end(a));

    vector<int> sum1(n + 1), sum2(n + 1);
    for(int i = 0; i < n; ++i) {
        sum1[i + 1] = sum1[i] + a[i];
        sum2[i + 1] = sum2[i] + (s[i] == '1' ? a[i] : 0);
    }

    int ans = sum2[n] - sum2[0];
    for(int i = 0; i < n; ++i) {
        if(s[i] == '1') {
            ans = max(ans, sum1[n] - sum1[i + 1] + sum2[i]);
        }
    }

    cout << ans << endl;
}
