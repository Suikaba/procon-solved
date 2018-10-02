// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0369

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, t; cin >> n >> t;
    double a = 0;
    for(int i = 0; i < n; ++i) {
        double x, h; cin >> x >> h;
        a = max(a, h / x);
    }
    cout << fixed << setprecision(10) << t * a << endl;
}
