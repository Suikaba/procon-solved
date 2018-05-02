#include <bits/stdc++.h>
using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0641

int main() {
    int n, a, b, c, d;
    cin >> n >> a >> b >> c >> d;
    cout << min((n + a - 1) / a * b, (n + c - 1) / c * d) << endl;
}
