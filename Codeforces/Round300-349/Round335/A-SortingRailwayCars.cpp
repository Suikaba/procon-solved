#include <bits/stdc++.h>
using namespace std;

// http://codeforces.com/contest/605/problem/A

// 反省点
// なんでこの問題で考察をミスするかね．
// もっと落ち着くこと．

constexpr int inf = 1e9;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> pos(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
        pos[a[i] - 1] = i;
    }
    int ans = inf;
    for(int l = 0; l < n; l++) {
        int now = 1;
        while(l + 1 < n && pos[l] < pos[l + 1]) {
            now += 1;
            l++;
        }
        ans = min(ans, n - now);
    }

    cout << ans << endl;
}
