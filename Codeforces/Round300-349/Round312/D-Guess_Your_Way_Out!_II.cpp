
// http://codeforces.com/contest/558/problem/D

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int h, q;
    cin >> h >> q;
    const ll lb = 1LL << (h - 1), ub = (1LL << h) - 1;
    vector<ll> xs = {lb, ub};
    vector<ll> l(q), r(q), ans(q);
    for(int i = 0; i < q; ++i) {
        ll ti;
        scanf("%lld %lld %lld %lld", &ti, &l[i], &r[i], &ans[i]);
        while(ti++ != h) {
            l[i] *= 2;
            r[i] = r[i] * 2 + 1;
        }
        xs.push_back(l[i]);
        xs.push_back(r[i]);
        if(l[i] != lb) xs.push_back(l[i] - 1);
        if(l[i] != ub) xs.push_back(l[i] + 1);
        if(r[i] != lb) xs.push_back(r[i] - 1);
        if(r[i] != ub) xs.push_back(r[i] + 1);
    }
    sort(begin(xs), end(xs));
    xs.erase(unique(begin(xs), end(xs)), end(xs));
    const int n = xs.size();
    vector<int> imos(n + 1);
    for(int i = 0; i < q; ++i) {
        l[i] = lower_bound(begin(xs), end(xs), l[i]) - begin(xs);
        r[i] = lower_bound(begin(xs), end(xs), r[i]) - begin(xs);
        if(ans[i] == 1) {
            imos[l[i]] += 1;
            imos[r[i] + 1] -= 1;
        } else {
            imos[l[i]] -= 1;
            imos[r[i] + 1] += 1;
        }
    }
    for(int i = 0; i < n; ++i) {
        imos[i + 1] += imos[i];
    }
    const int found_cnt = accumulate(begin(ans), end(ans), 0);
    for(int i = 0; i < n; ++i) {
        imos[i] = imos[i] == found_cnt;
    }

    vector<ll> cand;
    for(int i = 0; i < n; ++i) {
        if(imos[i] == 1) {
            cand.push_back(xs[i]);
            if(i != n - 1 && (xs[i] + 1 != xs[i + 1])) {
                cand.push_back(xs[i]);
            }
        }
    }

    if(cand.size() >= 2u) {
        cout << "Data not sufficient!" << endl;
    } else if(cand.empty()) {
        cout << "Game cheated!" << endl;
    } else {
        cout << cand.back() << endl;
    }
}
