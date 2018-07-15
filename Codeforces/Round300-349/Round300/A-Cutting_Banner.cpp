
// http://codeforces.com/contest/538/problem/A

#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    const int n = s.size();
    bool ok = false;
    for(int l = 0; l < n; ++l) {
        for(int r = 1; r <= n; ++r) {
            string t;
            for(int i = 0; i < n; ++i) {
                if(l <= i && i < r) continue;
                t += s[i];
            }
            ok |= t == "CODEFORCES";
        }
    }
    cout << (ok ? "YES" : "NO") << endl;
}
