
// http://codeforces.com/contest/557/problem/A

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> mi(3), ma(3);
    for(int i = 0; i < 3; ++i) {
        cin >> mi[i] >> ma[i];
    }

    vector<int> ans(3);
    int sum = 0;
    for(int i = 0; i < 3; ++i) {
        ans[i] = ma[i];
        sum += ans[i];
    }
    for(int i = 2; i >= 0 && sum > n; --i) {
        int d = min(sum - n, ans[i] - mi[i]);
        sum -= d;
        ans[i] -= d;
    }

    for(int i = 0; i < 3; ++i) {
        cout << ans[i] << " \n"[i + 1 == 3];
    }
}
