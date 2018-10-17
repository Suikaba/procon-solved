// http://codeforces.com/contest/573/problem/B

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> h(n + 2);
    for(int i = 1; i <= n; ++i) {
        cin >> h[i];
    }

    auto calc = [n] (vector<int> hs, bool rev = false) {
        if(rev) reverse(begin(hs), end(hs));
        vector<int> vs(n + 2);
        int mini = 0;
        for(int i = 1; i <= n; ++i) {
            mini++;
            if(mini > hs[i]) mini = hs[i];
            vs[i] = mini;
        }
        if(rev) reverse(begin(vs), end(vs));
        return vs;
    };
    auto left = calc(h), right = calc(h, true);

    int ans = 0;
    for(int i = 1; i <= n; ++i) {
        ans = max(ans, min(left[i], right[i]));
    }

    cout << ans << endl;
}
