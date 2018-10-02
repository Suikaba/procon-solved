// http://codeforces.com/contest/1041/problem/E

#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
    int n; cin >> n;
    vector<int> cnt(n + 1);
    for(int i = 0; i < n - 1; ++i) {
        int a, b; cin >> a >> b;
        cnt[a]++, cnt[b]++;
    }
    if(cnt[n] != n - 1 || cnt[1] >= 2) {
        cout << "NO" << endl;
        return 0;
    }
    vector<bool> can_use(n + 1);
    vector<int> leafs;
    for(int i = 1; i < n; ++i) {
        if(cnt[i] > 0) leafs.push_back(i);
        else           can_use[i] = true;
    }

    vector<pii> ans;
    while(!leafs.empty()) {
        const auto v = leafs.back();
        leafs.pop_back();
        auto pre = v;
        while(cnt[v] > 1) {
            cnt[v]--;
            int use = -1;
            for(int i = v - 1; i >= 0; --i) {
                if(can_use[i]) {
                    use = i;
                    can_use[i] = false;
                    break;
                }
            }
            if(use == -1) {
                cout << "NO" << endl;
                return 0;
            }
            ans.emplace_back(pre, use);
            pre = use;
        }
        ans.emplace_back(pre, n);
    }

    cout << "YES" << endl;
    for(auto& p : ans) {
        cout << p.first << ' ' << p.second << endl;
    }
}
