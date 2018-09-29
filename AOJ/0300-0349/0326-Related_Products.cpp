// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0326

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, f; cin >> n >> f;
    map<pair<string, string>, int> cnt;
    for(int i = 0; i < n; ++i) {
        int m; cin >> m;
        vector<string> v(m);
        for(int j = 0; j < m; ++j) {
            cin >> v[j];
        }
        sort(begin(v), end(v));
        for(int j = 0; j < m; ++j) {
            for(int k = j + 1; k < m; ++k) {
                cnt[make_pair(v[j], v[k])] += 1;
            }
        }
    }
    vector<pair<string, string>> ans;
    for(auto& p : cnt) {
        if(p.second >= f) ans.push_back(p.first);
    }
    cout << ans.size() << endl;
    for(auto& p : ans) {
        cout << p.first << " " << p.second << endl;
    }
}
