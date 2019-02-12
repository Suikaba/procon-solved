#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<int> ans(n);
    set<int> s;
    for(int i = 1; i <= n; ++i) {
        s.insert(i);
    }
    for(int i = 0; i < m; ++i) {
        int l, r, x; cin >> l >> r >> x;
        auto fst = s.lower_bound(l), lst = s.upper_bound(r);
        for(auto it = fst; it != lst; ++it) {
            if(*it == x) continue;
            ans[*it - 1] = x;
        }
        s.erase(fst, lst);
        s.insert(x);
    }
    for(int i = 0; i < n; ++i) {
        cout << ans[i] << " \n"[i + 1 == n];
    }
}