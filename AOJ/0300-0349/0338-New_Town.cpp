
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0338

#include <bits/stdc++.h>
using namespace std;

int main() {
    int w, h, c;
    cin >> w >> h >> c;
    cout << w * h / __gcd(w, h) / __gcd(w, h) * c << endl;
}
