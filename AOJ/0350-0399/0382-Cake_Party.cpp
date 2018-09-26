// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0382

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, c; cin >> n >> c;
    n += 1;
    int sum = 0;
    for(int i = 0; i < c; ++i) {
        int p; cin >> p;
        sum += p;
    }
    cout << (sum / n) + !!(sum % n) << endl;
}
