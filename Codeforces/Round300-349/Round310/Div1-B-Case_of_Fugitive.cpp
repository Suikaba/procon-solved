
// http://codeforces.com/contest/555/problem/B

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

int main() {
    int n, m; cin >> n >> m;
    vector<ll> l(n), r(n);
    for(int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
    }
    vector<tuple<ll, ll, ll>> range(n - 1);
    for(int i = 0; i + 1 < n; ++i) {
        range[i] = make_tuple(l[i + 1] - r[i], r[i + 1] - l[i], i);
    }
    sort(begin(range), end(range));
    vector<pll> a(m);
    for(int i = 0; i < m; ++i) {
        cin >> a[i].first;
        a[i].second = i + 1;
    }
    sort(begin(a), end(a));

    set<pll> s;
    vector<int> ans(n - 1, -1);
    for(int i = 0, j = 0; i < m; ++i) {
        while(j < n - 1 && get<0>(range[j]) <= a[i].first) {
            s.emplace(get<1>(range[j]), get<2>(range[j]));
            j++;
        }
        auto it = s.lower_bound(make_pair(a[i].first, -1));
        if(it == end(s)) continue;
        ans[it->second] = a[i].second;
        s.erase(it);
    }

    if(*min_element(begin(ans), end(ans)) == -1) {
        cout << "No" << endl;
    } else {
        cout << "Yes" << endl;
        for(int i = 0; i < n - 1; ++i) {
            cout << ans[i] << " \n"[i + 1 == n - 1];
        }
    }
}
