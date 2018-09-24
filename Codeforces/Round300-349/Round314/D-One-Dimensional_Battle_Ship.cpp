#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
    int n, k, a; cin >> n >> k >> a;
    int m; cin >> m;
    vector<int> x(m);
    for(int i = 0; i < m; ++i) {
        cin >> x[i];
    }

    set<pii> segs;
    segs.emplace(1, n);
    int maxi = (n + 1) / (a + 1);
    int ans = -1;
    for(int i = 0; i < m; ++i) {
        auto it = segs.upper_bound(make_pair(x[i], n + 1));
        if(it != begin(segs)) {
            it = prev(it);
            if(it->first <= x[i] && x[i] <= it->second) {
                maxi -= (it->second - it->first + 2) / (a + 1);
                if(it->first != x[i]) {
                    maxi += (x[i] - it->first + 1) / (a + 1);
                    segs.emplace(it->first, x[i] - 1);
                }
                if(it->second != x[i]) {
                    maxi += (it->second - x[i] + 1) / (a + 1);
                    segs.emplace(x[i] + 1, it->second);
                }
                segs.erase(it);
            }
        }
        assert(maxi >= 0);
        if(maxi < k) {
            ans = i + 1;
            break;
        }
    }

    cout << ans << endl;
}
