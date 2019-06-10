#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
using ll = long long;

int main() {
    int T; cin >> T;
    while(T--) {
        ll n; cin >> n;
        vector<pii> ans = {{-1, -1}, {0, 0}};
        int p = 62;
        while(!((1LL << p) & n)) p -= 1;
        while(--p >= 0) {
            if(n & (1LL << p)) {
                const int id = (int)ans.size() - 2;
                ans.emplace_back(id + 1, id);
                ans.emplace_back(id + 1, id + 1);
            } else {
                const int id = (int)ans.size() - 2;
                ans.emplace_back(id, id);
                ans.emplace_back(id + 1, id);
            }
        }

        cout << ans.size() << endl;
        for(auto [l, r] : ans) {
            cout << l << " " << r << "\n";
        }
        cout << (int)ans.size() - 2 << endl;
    }
}
