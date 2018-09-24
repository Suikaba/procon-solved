
// http://codeforces.com/contest/570/problem/A

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m; cin >> n >> m;
    vector<int> cnt(n);
    for(int i = 0; i < m; ++i) {
        vector<int> a(n);
        for(int j = 0; j < n; ++j) {
            cin >> a[j];
        }
        cnt[max_element(begin(a), end(a)) - begin(a)] += 1;
    }
    cout << (max_element(begin(cnt), end(cnt)) - begin(cnt)) + 1 << endl;
}
