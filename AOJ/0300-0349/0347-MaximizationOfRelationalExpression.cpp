#include <bits/stdc++.h>
using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0347

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    multiset<int, greater<int>> s;
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
        s.insert(a[i]);
    }

    double ans = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {
            s.erase(a[i]);
            s.erase(a[j]);
            double x = abs(a[i] - a[j]);
            double y = *s.begin() + *(next(s.begin()));
            s.insert(a[i]);
            s.insert(a[j]);
            ans = max(ans, y / x);
        }
    }

    cout << fixed << setprecision(10) << ans << endl;
}
