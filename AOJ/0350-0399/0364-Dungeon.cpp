// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0364

#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
    int w, h, n; cin >> w >> h >> n;
    vector<pii> es(n);
    multiset<int, greater<>> s;
    for(int i = 0; i < n; ++i) {
        cin >> es[i].first >> es[i].second;
        s.insert(es[i].second);
    }
    sort(begin(es), end(es));
    int ans = 1e9;
    {
        int maxi_y = 0;
        for(int i = 0; i < n; ++i) {
            maxi_y = max(maxi_y, es[i].second);
        }
        ans = min(es.back().first, maxi_y);
    }
    for(int i = 0; i < n; ++i) {
        s.erase(s.lower_bound(es[i].second));
        ans = min(ans, es[i].first + *begin(s));
    }
    cout << ans << endl;
}
