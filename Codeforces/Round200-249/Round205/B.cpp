#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    map<int, vector<int>> pos;
    for(int i = 0; i < 2 * n; ++i) {
        int a; cin >> a;
        pos[a].push_back(i);
    }

    vector<int> s1, s2;
    vector<int> ans(2 * n, -1);
    vector<bool> used(100);
    for(auto& p : pos) {
        if(p.second.size() >= 2u && (int)s1.size() < n) {
            used[p.first] = true;
            ans[p.second.back()] = 1;
            p.second.pop_back();
            ans[p.second.back()] = 2;
            p.second.pop_back();
            s1.push_back(p.first);
            s2.push_back(p.first);
        }
    }

    for(auto& p : pos) {
        auto& v = p.second;
        if(used[p.first] || v.empty()) continue;
        if(s1.size() == s2.size()) {
            ans[v.back()] = 1;
            s1.push_back(p.first);
            used[p.first] = true;
            v.pop_back();
        } else {
            ans[v.back()] = 2;
            s2.push_back(p.first);
            used[p.first] = true;
            v.pop_back();
        }
    }
    for(auto& p : pos) {
        for(auto i : p.second) {
            if((int)s1.size() < n) {
                ans[i] = 1;
                s1.push_back(p.first);
            } else {
                ans[i] = 2;
                s2.push_back(p.first);
            }
        }
    }

    set<int> s;
    for(auto x : s1) {
        for(auto y : s2) {
            s.insert(x * 100 + y);
        }
    }

    cout << s.size() << endl;
    for(int i = 0; i < 2 * n; ++i) {
        cout << ans[i] << " \n"[i + 1 == 2 * n];
    }
}
