#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
using ll = long long;

int main() {
    int n, k;
    cin >> n >> k;
    vector<tuple<int, int, int>> knights(n);
    vector<int> p(n), c(n);
    for(int i = 0; i < n; ++i) {
        cin >> p[i];
    }
    for(int i = 0; i < n; ++i) {
        cin >> c[i];
        knights[i] = make_tuple(p[i], c[i], i);
    }
    sort(begin(knights), end(knights));

    multiset<int> s;
    ll sum = 0;
    vector<ll> ans(n);
    for(int i = 0; i < n; ++i) {
        int x, c, id;
        tie(x, c, id) = knights[i];
        if((int)s.size() > k) {
            sum -= *s.begin();
            s.erase(s.begin());
        }
        ans[id] = sum + c;
        s.insert(c);
        sum += c;
    }

    for(int i = 0; i < n; ++i) {
        cout << ans[i] << " \n"[i + 1 == n];
    }
}
