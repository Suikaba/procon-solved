#include <bits/stdc++.h>
using namespace std;

// http://codeforces.com/problemset/problem/528/B

// これはすぐわかった．
// TDPC のターゲットと全く一緒ですね（まあこんなのは大量に出題されてそう

using pii = pair<int, int>;

constexpr int inf = numeric_limits<int>::max();

int main() {
    int n;
    cin >> n;
    vector<pii> p(n);
    for(int i = 0; i < n; ++i) {
        cin >> p[i].first >> p[i].second;
    }
    sort(begin(p), end(p));

    vector<int> dp(n, inf);
    for(int i = 0; i < n; ++i) {
        auto it = upper_bound(begin(dp), end(dp), p[i].first - p[i].second);
        *it = min(*it, p[i].first + p[i].second);
    }

    cout << (find(begin(dp), end(dp), inf) - begin(dp)) << endl;
}
