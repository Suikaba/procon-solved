#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

int main() {
    int T; cin >> T;
    while(T--) {
        int n; cin >> n;
        int alpha; cin >> alpha;
        int m; cin >> m;
        bool pushed = false;
        vector<int> p, a, b;
        for(int i = 0; i < n; ++i) {
            int tl, ta, tb; cin >> tl >> ta >> tb;
            if(tl > alpha && !pushed) {
                p.push_back(alpha);
                a.push_back(0), b.push_back(0);
                pushed = true;
            }
            p.push_back(tl), a.push_back(ta), b.push_back(tb);
        }
        if(!pushed) {
            p.push_back(alpha);
            a.push_back(0), b.push_back(0);
            pushed = true;
        }
        n = n + 1;

        function<int()> solve =
            [&] () {
                const int apos = find(begin(p), end(p), alpha) - begin(p);

                int res = 2 * abs(p.back() - p[0]);
                vector<int> cnt(m + 1);
                for(int i = apos + 1; i < n; ++i) {
                    cnt[a[i]] += 1;
                }
                int r = n - 1;
                int mini = inf;
                for(int l = apos; l >= 0; --l) {
                    while(r > apos && cnt[b[r]] > 0) {
                        cnt[b[r]] -= 1;
                        r--;
                    }
                    mini = min(mini, abs(p[r] - p[l]));
                    assert(mini >= 0);
                    if(l == 0) continue;
                    cnt[a[l - 1]] += 1;
                }
                return res + 2 * mini;
            };
        int ans = solve();
        reverse(begin(p), end(p));
        reverse(begin(a), end(a));
        reverse(begin(b), end(b));
        ans = min(ans, solve());

        cout << ans << endl;
    }
}
