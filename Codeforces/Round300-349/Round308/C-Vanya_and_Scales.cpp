
// http://codeforces.com/contest/552/problem/C

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ll w, m; cin >> w >> m;
    if(w == 2) {
        cout << "YES" << endl;
    } else {
        vector<ll> v;
        {
            ll now = 1;
            while(now < m) {
                v.push_back(now);
                now *= w;
            }
            v.push_back(now);
        }
        const int n1 = v.size() / 2;
        const int n2 = v.size() - n1;
        vector<ll> v1 = {0}, v2 = {0};
        for(int i = 0; i < n1; ++i) {
            vector<ll> add;
            for(auto x : v1) {
                add.push_back(x + v[i]);
                add.push_back(x - v[i]);
            }
            v1.insert(end(v1), begin(add), end(add));
        }
        for(int i = 0; i < n2; ++i) {
            vector<ll> add;
            for(auto x : v2) {
                add.push_back(x + v[i + n1]);
                add.push_back(x - v[i + n1]);
            }
            v2.insert(end(v2), begin(add), end(add));
        }
        sort(begin(v1), end(v1)); sort(begin(v2), end(v2));
        v1.erase(unique(begin(v1), end(v1)), end(v1));
        v2.erase(unique(begin(v2), end(v2)), end(v2));

        bool ans = false;
        for(auto x : v1) {
            ans |= (*lower_bound(begin(v2), end(v2), x + m) == x + m);
            ans |= (*lower_bound(begin(v2), end(v2), x - m) == x - m);
            ans |= (*lower_bound(begin(v2), end(v2), m - x) == m - x);
            ans |= (*lower_bound(begin(v2), end(v2), -m - x) == -x - m);
        }
        cout << (ans ? "YES" : "NO") << endl;
    }
}
