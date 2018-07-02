
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0337

#include <bits/stdc++.h>
using namespace std;

int main() {
    int e, y;
    cin >> e >> y;
    if(e == 0) {
        if(y <= 1911) cout << "M" << (y - 1867) << endl;
        else if(y <= 1925) cout << "T" << (y - 1911) << endl;
        else if(y <= 1988) cout << "S" << y - 1925 << endl;
        else cout << "H" << y - 1988 << endl;
    } else if(e == 1) {
        cout << 1867 + y << endl;
    } else if(e == 2) {
        cout << 1911 + y << endl;
    } else if(e == 3) {
        cout << 1925 + y << endl;
    } else {
        cout << 1988 + y << endl;
    }
}
