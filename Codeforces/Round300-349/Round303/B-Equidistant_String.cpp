
// http://codeforces.com/contest/545/problem/B

#include <bits/stdc++.h>
using namespace std;

int main() {
    string s, t;
    cin >> s >> t;
    const int n = s.size();
    int diff = 0;
    for(int i = 0; i < n; ++i) {
        diff += s[i] != t[i];
    }
    if(abs(diff) & 1) {
        cout << "impossible" << endl;
    } else {
        diff /= 2;
        for(int i = 0; i < n; ++i) {
            if(s[i] == t[i]) {
                cout << s[i];
            } else {
                if(diff > 0) cout << s[i];
                else cout << t[i];
                diff--;
            }
        }
        cout << endl;
    }
}
