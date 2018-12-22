#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, k; cin >> n >> m >> k;
    vector<int> a(k);
    for(int i = 0; i < k; ++i) {
        cin >> a[i];
        a[i]--;
    }

    if(n == k) {
        cout << -1 << endl;
        return 0;
    }
    if(m > (n - 1) * (n - 2) / 2 + (n - k)) {
        cout << -1 << endl;
        return 0;
    }

    vector<int> b;
    for(int i = 0; i < n; ++i) {
        if(find(begin(a), end(a), i) == end(a)) b.push_back(i);
    }
    const int u = a[0];
    int remain = m;
    for(int i = 0; i < n && remain > 1; ++i) {
        if(i == u || i == b[0]) continue;
        cout << min(i, b[0]) + 1 << ' ' << max(i, b[0]) + 1 << endl;
        remain--;
    }
    for(int i = 0; i < n && remain > 1; ++i) {
        for(int j = i + 1; j < n && remain > 1; ++j) {
            if(i == b[0] || j == b[0] || i == u || j == u) continue;
            cout << i + 1 << ' ' << j + 1 << endl;
            remain--;
        }
    }
    for(int i = 0; i < (int)b.size() && remain > 0; ++i) {
        cout << min(u + 1, b[i] + 1) << ' ' << max(u + 1, b[i] + 1) << endl;
        remain--;
    }
}
