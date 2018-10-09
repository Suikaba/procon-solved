// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2881

#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    while(cin >> s, s[0] != '#') {
        int y, m, d; cin >> y >> m >> d;
        if(y <= 30 || (y == 31 && m < 5)) {
            cout << "HEISEI" << " " << y << ' ' << m << ' ' << d << endl;
        } else {
            cout << "? " << y - 30 << ' ' << m << ' ' << d << endl;
        }
    }
}
