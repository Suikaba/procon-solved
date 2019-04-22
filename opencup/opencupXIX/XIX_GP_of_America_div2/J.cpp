#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    string s, t; cin >> s >> t;
    const int n = s.size(), m = t.size();

    vector<vector<int> > pos(26);
    for(int i = 0; i < n; ++i) {
        pos[s[i] - 'a'].push_back(i);
    }

    ll ans = 0;
    for(int i = 0; i < n; ++i) {
        int cur = i;
        for(int j = 0; j < m; ++j) {
            const vector<int>& ps = pos[t[j] - 'a'];
            const int idx = lower_bound(ps.begin(), ps.end(), cur) - ps.begin();
            if(idx == (int)ps.size()) {
                cur = -1;
                break;
            }
            cur = ps[idx] + 1;
        }
        if(cur == -1) continue;
        ans += n - cur + 1;
    }

    cout << ans << endl;
}
