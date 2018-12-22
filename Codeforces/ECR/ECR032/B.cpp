#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    string s; cin >> s;

    int v = 0, h = 0;
    for(int i = 0; i < n; ++i) {
        if(s[i] == 'U') v -= 1;
        if(s[i] == 'D') v += 1;
        if(s[i] == 'L') h -= 1;
        if(s[i] == 'R') h += 1;
    }

    cout << n - abs(v) - abs(h) << endl;
}
