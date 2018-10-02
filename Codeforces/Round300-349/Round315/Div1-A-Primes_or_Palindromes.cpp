// http://codeforces.com/contest/568/problem/A

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    constexpr int max_p = 3e6;
    ll p, q; cin >> p >> q;
    vector<int> ps;
    vector<bool> is_prime(max_p, true);
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i < max_p; ++i) {
        if(is_prime[i]) {
            ps.push_back(i);
            for(int j = i + i; j < max_p; j += i) {
                is_prime[j] = false;
            }
        }
    }

    auto is_palm = [&] (int x) {
        auto s = to_string(x);
        const int n = s.size();
        for(int i = 0; i < n; ++i) {
            if(s[i] != s[n - 1 - i]) return false;
        }
        return true;
    };
    vector<ll> ps2;
    for(int i = 1; i < max_p; ++i) {
        if(is_palm(i)) ps2.push_back(i);
    }

    auto pi = [&] (ll ub) {
        return upper_bound(begin(ps), end(ps), ub) - begin(ps);
    };
    auto rub = [&] (ll ub) {
        return upper_bound(begin(ps2), end(ps2), ub) - begin(ps2);
    };

    int ans = -1;
    for(int x = max_p - 1; x >= 1; --x) {
        if(q * pi(x) <= p * rub(x)) {
            ans = x;
            break;
        }
    }

    if(ans == -1) {
        cout << "Palindromic tree is better than splay tree" << endl;
    } else {
        cout << ans << endl;
    }
}
