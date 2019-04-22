#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    string name; cin >> name; // ha???
    int m, s; cin >> m >> s;
    int T; cin >> T;
    while(T--) {
        char c; int x; cin >> c >> x;
        if(c == 'R') {
            s = min(m, s + x);
        } else {
            s = max(0, s - x);
        }
    }

    cout << name << ' ' << s << endl;
}
