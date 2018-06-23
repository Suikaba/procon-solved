#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ll n;
    cin >> n;
    ll lb = 0, ub = n;
    while(ub - lb > 1) {
        const auto mid = (ub + lb) / 2;
        ll now = n, eat = 0;
        while(now > 0) {
            eat += min(mid, now);
            now -= min(now, mid);
            now -= now / 10;
        }
        if(n <= eat * 2) ub = mid;
        else         lb = mid;
    }
    cout << ub << endl;
}
