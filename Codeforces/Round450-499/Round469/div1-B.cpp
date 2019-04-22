#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ll n, q; cin >> n >> q;
    while(q--) {
        ll x; cin >> x;
        ll st = 1, lst = x, bk = n;
        while(lst % 2 == 0) {
            const ll nxt = (lst - st - 1) / 2 + 1 + bk;
            st = lst;
            bk = lst = nxt;
        }

        cout << (lst + 1) / 2 << endl;
    }
}