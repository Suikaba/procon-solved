#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
    string s; cin >> s;
    set<int> zero, one;
    for(int i = 0; i < (int)s.size(); ++i) {
        (s[i] == '0' ? zero : one).insert(i);
    }
    vector<vector<int>> ans;
    while(!zero.empty()) {
        vector<int> cur = {*zero.begin()};
        zero.erase(zero.begin());
        while(true) {
            auto it = one.lower_bound(cur.back());
            if(it == one.end()) break;
            auto it2 = zero.lower_bound(*it);
            if(it2 == zero.end()) break;
            cur.push_back(*it);
            cur.push_back(*it2);
            one.erase(it);
            zero.erase(it2);
        }
        ans.push_back(move(cur));
    }

    if(!one.empty()) {
        cout << -1 << endl;
    } else {
        cout << ans.size() << endl;
        for(auto const& v : ans) {
            const int sz = v.size();
            cout << sz << " ";
            for(int i = 0; i < sz; ++i) {
                cout << v[i] + 1 << " \n"[i + 1 == sz];
            }
        }
    }
}