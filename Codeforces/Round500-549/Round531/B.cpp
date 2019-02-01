#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k; cin >> n >> k;
    map<int, vector<int>> pos;
    for(int i = 0; i < n; ++i) {
        int a; cin >> a;
        pos[a].push_back(i);
    }

    for(auto const& p : pos) {
        if((int)p.second.size() > k) {
            cout << "NO" << endl;
            return 0;
        }
    }

    int it = 0;
    vector<int> ans(n);
    for(auto const& p : pos) {
        auto const& v = p.second;
        for(auto i : v) {
            ans[i] = (it + 1);
            it = (it + 1) % k;
        }
    }

    cout << "YES" << endl;
    for(int i = 0; i < n; ++i) {
        cout << ans[i] << " \n"[i + 1 == n];
    }
}
