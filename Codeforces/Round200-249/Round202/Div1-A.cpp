#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    auto check = [&] (ll cnt) {
        ll remain = cnt;
        for(int i = 0; i < n && remain > 0; ++i) {
            remain -= cnt - a[i];
        }
        return remain <= 0;
    };
    ll lb = *max_element(begin(a), end(a)) - 1, ub = 1e10;
    while(ub - lb > 1) {
        const auto mid = (ub + lb) >> 1;
        (check(mid) ? ub : lb) = mid;
    }
    cout << ub << endl;
}
