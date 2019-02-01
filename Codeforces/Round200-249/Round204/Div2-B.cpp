#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
    int n; cin >> n;
    map<int, vector<int>> pos;
    for(int i = 0; i < n; ++i) {
        int a; cin >> a;
        pos[a].push_back(i);
    }

    vector<pii> ans;
    for(auto& p : pos) {
        if(p.second.size() == 1u) {
            ans.emplace_back(p.first, 0);
        } else {
            const int sz = p.second.size();
            const int d = p.second[1] - p.second[0];
            bool ok = true;
            for(int i = 2; i < sz; ++i) {
                ok &= p.second[i] - p.second[i - 1] == d;
            }
            if(ok) {
                ans.emplace_back(p.first, d);
            }
        }
    }

    cout << ans.size() << endl;
    for(auto& p : ans) {
        cout << p.first << ' ' << p.second << endl;
    }
}
