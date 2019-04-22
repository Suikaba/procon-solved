#include <bits/stdc++.h>
using namespace std;

int main() {
    string s, t; cin >> s >> t;
    const int n = min(s.size(), t.size());

    string ans;
    for(int i = 1; i <= n; ++i) {
        const auto tt = s.substr(0, i);
        if(s.size() % tt.size() != 0 || t.size() % tt.size() != 0) continue;
        bool check = true;
        for(int j = 0; j < (int)s.size(); j += i) {
            check &= tt == s.substr(j, i);
        }
        for(int j = 0; j < (int)t.size(); j += i) {
            check &= tt == t.substr(j, i);
        }
        if(check) {
            ans = tt;
            break;
        }
    }

    if(ans == "") {
        cout << "No solution" << endl;
    } else {
        cout << ans << endl;
    }
}