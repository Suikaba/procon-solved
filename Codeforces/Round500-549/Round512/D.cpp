#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ll n, m, k; cin >> n >> m >> k;
    ll a = n * m, b = k;
    ll g = __gcd(a, b);
    a /= g, b /= g;
    if(b != 1 && b != 2) {
        cout << "NO" << endl;
        return 0;
    }
    const ll gn = __gcd(n, g);
    ll x = n / gn;
    g /= gn;
    ll y = m / g;
    if(b == 1) {
        if(y * 2 <= m) y *= 2;
        else           x *= 2;
    }
    if(x > n || y > m) {
        cout << "NO" << endl;
        return 0;
    }
    cout << "YES" << endl;
    cout << 0 << " " << 0 << endl;
    cout << x << " " << 0 << endl;
    cout << 0 << " " << y << endl;
}