
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0336

#include <bits/stdc++.h>
using namespace std;

int main() {
    int h, r;
    cin >> h >> r;
    if(h + r < 0) {
        cout << -1 << endl;
    } else if(h + r > 0) {
        cout << 1 << endl;
    } else {
        cout << 0 << endl;
    }
}
