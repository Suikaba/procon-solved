#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    string s = "<3";
    for(int i = 0; i < n; ++i) {
        string t; cin >> t;
        s += t + "<3";
    }
    string t; cin >> t;
    const int m = t.size();

    int p = 0;
    for(int i = 0; i < m && p < (int)s.size(); ++i) {
        p += s[p] == t[i];
    }

    if(p == (int)s.size()) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }
}
