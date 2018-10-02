// http://codeforces.com/contest/1041/problem/C

#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
    int n, m, d; cin >> n >> m >> d;
    set<pii> s;
    for(int i = 0; i < n; ++i) {
        int a; cin >> a;
        s.emplace(a, i);
    }

    vector<int> ans(n);
    for(int day = 1; !s.empty(); ++day) {
        auto now = *s.begin();
        ans[now.second] = day;
        s.erase(now);
        while(true) {
            auto it = s.upper_bound(make_pair(now.first + d, 1e9));
            if(end(s) == it) break;
            now = *it;
            s.erase(now);
            ans[now.second] = day;
        }
    }

    cout << *max_element(begin(ans), end(ans)) << endl;
    for(int i = 0; i < n; ++i) {
        cout << ans[i] << " \n"[i + 1 == n];
    }
}
