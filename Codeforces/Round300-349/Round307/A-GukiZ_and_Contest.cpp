
// http://codeforces.com/contest/551/problem/A

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n), as;
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i] = -a[i];
        as.push_back(a[i]);
    }
    sort(begin(as), end(as));
    as.erase(unique(begin(as), end(as)), end(as));
    vector<int> cnt(as.size() + 1);
    for(int i = 0; i < n; ++i) {
        a[i] = lower_bound(begin(as), end(as), a[i]) - begin(as);
        cnt[a[i] + 1] += 1;
    }
    for(int i = 0; i < (int)as.size(); ++i) {
        cnt[i + 1] += cnt[i];
    }
    for(int i = 0; i < n; ++i) {
        cout << cnt[a[i]] + 1 << " \n"[i + 1 == n];
    }
}
