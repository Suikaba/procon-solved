// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0371

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> t(n);
    for(int i = 0; i < n; ++i) {
        cin >> t[i];
    }

    const int ma = *max_element(begin(t), end(t));
    vector<int> ps;
    for(int i = 1; i <= ma; ++i) {
        if(ma % i == 0) ps.push_back(i);
    }

    int ans = 0;
    for(int i = 0; i < n; ++i) {
        ans += *lower_bound(begin(ps), end(ps), t[i]) - t[i];
    }
    cout << ans << endl;
}
