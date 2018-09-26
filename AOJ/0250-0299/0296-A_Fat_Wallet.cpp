// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0296

#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> a = {1, 5, 10, 50, 100, 500};
    int tot = 0;
    for(int i = 0; i < 6; ++i) {
        int c; cin >> c;
        tot += c * a[i];
    }
    cout << (tot >= 1000) << endl;
}
