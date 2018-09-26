// http://codeforces.com/contest/584/problem/C

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, t; cin >> n >> t;
    string s1, s2; cin >> s1 >> s2;
    string ans;
    for(int i = 0; i < n; ++i) {
        for(char c = 'a'; c <= 'z'; ++c) {
            if(s1[i] != c && s2[i] != c) {
                ans += c;
                break;
            }
        }
    }
    t -= n;
    for(int i = 0; i < n && t < 0; ++i) {
        if(s1[i] == s2[i]) {
            ans[i] = s1[i];
            t += 1;
        }
    }
    bool f = false;
    for(int i = 0; i < n && t < 0; ++i) {
        if(s1[i] != s2[i]) {
            t += f;
            ans[i] = (f ? s1[i] : s2[i]);
            f = !f;
        }
    }

    if(t < 0) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
}
