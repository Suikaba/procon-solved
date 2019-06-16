#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    while(cin >> n, n) {
        multiset<int, greater<>> d;
        for(int i = 0; i < n * (n - 1) / 2; ++i) {
            int x; cin >> x;
            d.insert(x);
        }

        vector<int> cur = {0, *d.begin()}; // x position
        d.erase(d.begin());
        vector<vector<int>> ans;
        function<void(multiset<int, greater<>>&)> dfs = [&] (multiset<int, greater<>>& s) {
            if((int)cur.size() == n) { // ok
                ans.push_back({});
                for(int i = 1; i < n; ++i) {
                    ans.back().push_back(cur[i] - cur[i - 1]);
                }
                return;
            }
            auto attempt = [&] (int p) {
                vector<int> rm;
                for(auto x : cur) {
                    const auto it = s.lower_bound(abs(p - x));
                    if(it == end(s) || *it != abs(p - x)) break;
                    rm.push_back(*it);
                    s.erase(it);
                }
                if(rm.size() == cur.size()) {
                    cur.insert(lower_bound(begin(cur), end(cur), p), p);
                    dfs(s);
                    cur.erase(find(begin(cur), end(cur), p));
                }
                s.insert(begin(rm), end(rm));
            };
            attempt(*s.begin());
            attempt(cur.back() - *s.begin());
        };

        dfs(d);
        sort(begin(ans), end(ans));
        ans.erase(unique(begin(ans), end(ans)), end(ans));
        for(auto const& v : ans) {
            for(int i = 0; i < n - 1; ++i) {
                cout << v[i] << " \n"[i + 1 == n - 1];
            }
        }
        cout << "-----" << endl;
    }
}
