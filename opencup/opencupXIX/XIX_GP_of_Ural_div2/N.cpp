#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ll n; cin >> n;
    set<ll> ans;
    for(ll x = 1; x * x <= n; ++x) {
        if(n % x == 0) {
            if(x != 1) {
                const ll k = x - 1;
                if(n / k == n % k) {
                    ans.insert(k);
                }
            }
            if(n / x != 1) {
                const ll k = n / x - 1;
                if(n / k == n % k) {
                    ans.insert(k);
                }
            }
        }
    }
    cout << ans.size() << endl;
}
