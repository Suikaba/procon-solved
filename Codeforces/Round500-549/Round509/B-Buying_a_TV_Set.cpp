// http://codeforces.com/contest/1041/problem/B

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ll a, b, w, h; cin >> a >> b >> w >> h;
    const ll g = __gcd(w, h);
    w /= g, h /= g;
    cout << min(a / w, b / h) << endl;
}
