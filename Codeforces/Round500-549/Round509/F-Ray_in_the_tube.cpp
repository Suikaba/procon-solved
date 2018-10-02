// http://codeforces.com/contest/1041/problem/F

#include <bits/stdc++.h>
using namespace std;

int main() {
    constexpr int max_n = 1e9;
    int n, y1; cin >> n >> y1;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int m, y2; cin >> m >> y2;
    vector<int> b(m);
    for(int i = 0; i < m; ++i) {
        cin >> b[i];
    }

    int ans = 1;
    { // same position (corner case)
        sort(begin(a), end(a));
        sort(begin(b), end(b));
        for(int i = 0; i < n; ++i) {
            if(binary_search(begin(b), end(b), a[i])) {
                ans = 2;
                break;
            }
        }
    }
    for(int w = 1; w < max_n; w *= 2) {
        unordered_map<int, int> cnt;
        for(int i = 0; i < n; ++i) {
            cnt[a[i] % (2 * w)] += 1;
        }
        for(int i = 0; i < m; ++i) {
            cnt[(b[i] + w) % (2 * w)] += 1;
        }
        for(auto& p : cnt) {
            ans = max(ans, p.second);
        }
    }

    cout << ans << endl;
}
